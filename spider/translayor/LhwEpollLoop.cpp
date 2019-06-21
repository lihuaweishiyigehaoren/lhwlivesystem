/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEpollLoop.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

#include "LhwEpollLoop.h"
#include "Logging.h"

#include <signal.h>
#include <cassert>

namespace translayor
{
using namespace std::placeholders;

LhwEpollLoop *LhwEpollLoop::Get()
{
    static LhwEpollLoop epollLoop;
    return &epollLoop;
}

LhwEpollLoop::LhwEpollLoop() : _shutdown(false)
{
    LOG(LOG_DEBUG) << "LhwEpollLoop::LhwEpollLoop";

    sigset_t set;      // 设置进程信号
    sigemptyset(&set); // 清空进程信号设置
    sigaddset(&set, SIGPIPE); 
    sigprocmask(SIG_BLOCK, &set, NULL);

    _initialize();
}

LhwEpollLoop::~LhwEpollLoop()
{
    _shutdown = true;
}

void LhwEpollLoop::addFdToServer(NativeSocket socket, LhwServer *server)
{
    _servers.insert({socket, server});
}

/*
    *将一个流对象的指针添加到Loop中,这样Loop会帮助流对象监听输入与输出事件,一旦有输入输出到来会通过回调函数通知流对象
    **/
void LhwEpollLoop::AddStream(EPollStreamPtr stream)
{
    _streams[stream->GetNativeSocket()] = stream;
}

int32_t LhwEpollLoop::addEpollEvents(int32_t events, int32_t fd)
{
    NativeSocketEvent ev;
    ev.events = events;
    ev.data.fd = fd;

    return epoll_ctl(_eventfd, EPOLL_CTL_ADD, fd, &ev);
}

int32_t LhwEpollLoop::modifyEpollEvents(int32_t events, int32_t fd)
{
    NativeSocketEvent ev;
    ev.events = events;
    ev.data.fd = fd;

    return epoll_ctl(_eventfd, EPOLL_CTL_MOD, fd, &ev);
}

void LhwEpollLoop::_initialize()
{
    _eventfd = epoll_create(MAX_EVENT_COUNT);
    if (_eventfd == -1)
    {
        LOG(LOG_ERROR) << "epoll_create failed!";
        assert(0);
    }
}

void LhwEpollLoop::_run()
{
    auto func = std::bind(&LhwEpollLoop::_processEpollEventThread, this);
    std::thread listenThread(func); // 创建一个分支线程,回调到func函数
    listenThread.detach();          // 将子线程从主线程中剥离,好处:主程序不阻塞,且能销毁线程
}

void LhwEpollLoop::_processEpollEventThread()
{
    LOG(LOG_DEBUG) << "_processEpollEventThread";

    NativeSocketEvent events[MAX_EVENT_COUNT]; //当前的最大epoll事件

    while (!_shutdown)
    {
        int32_t nfds;
        nfds = epoll_wait(_eventfd, events, MAX_EVENT_COUNT, -1); // 返回套接字个数准备对I/O有需求
        if (-1 == nfds)
        // 有错误发生
        {
            // EINTR错误的产生：当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能返回一个EINTR错误
            // 例如：在socket服务器端，设置了信号捕获机制，有子进程，当在父进程阻塞于慢系统调用时由父进程捕获到了一个有效信号时，内核会致使accept返回一个EINTR错误(被中断的系统调用)。
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                LOG(LOG_ERROR) << "epoll_wait failed!";
                LOG(LOG_ERROR) << errno;
                exit(EXIT_FAILURE);
            }
        }

        _handleEpollEvent(_eventfd, events, nfds);
    }
}

void LhwEpollLoop::_handleEpollEvent(int32_t eventfd, NativeSocketEvent *events, int32_t nfds)
{
    for (int32_t i = 0; i < nfds; ++i)
    {
        int32_t fd;
        fd = events[i].data.fd;

        // 使用find函数,返回的是被查找元素的位置,没有则返回map.end()
        // _servers都是服务器套接字,如果发现之前存在,说明有客户端连过来了
        if (_servers.find(fd) != _servers.end())
        {
            _acceptClient(eventfd, fd);
            continue;
        }

        // 说明是客户端
        int32_t n = 0;
        if (events[i].events & EPOLLIN)
        {
            _Read(eventfd, fd, events[i].events);
        }

        if (events[i].events & EPOLLOUT)
        {
            
        }
    }
}

int32_t LhwEpollLoop::_acceptClient(int32_t eventfd, int32_t listenfd)
{
    LOG(LOG_DEBUG) << "_acceptClient";

    LhwServer *server = _servers.find(listenfd)->second;
    Collectioner connection = server->acceptClientOfServer(eventfd); // 接收新客户端连接

    if (connection != nullptr)
    {
        _streams[connection->GetNativeSocket()] = connection;
    }
}

    /*
    *响应epoll中数据流的读取事件,对原始数据进行特殊处理,并通知事件所属的流对象来从流中读取数据
    */
void LhwEpollLoop::_Read(int32_t eventfd, int32_t fd, uint32_t events)
{
    LOG(LOG_DEBUG) << "_Read";

    EPollStreamPtr stream = _streams[fd];

    char buffer[BUFSIZ];
    int32_t readSize;
    int32_t nread = stream->Receive(buffer, BUFSIZ, readSize);

    stream->SetEvents(events);

    if ((nread == -1 && errno != EAGAIN) || readSize == 0)
    {
        _streams.erase(fd);

        LOG(LOG_WARNING) << "errno: " << errno << ": " << strerror(errno) << ", nread: " << nread << ", n" << readSize;
        return;
    }

    _Enqueue(stream, buffer, readSize);
}

/*
    *将读取到的内容发送到系统的数据读取队列中,通知数据监听方来获取处理后的数据
    */
void LhwEpollLoop::_Enqueue(EPollStreamPtr stream, const char *buf, int64_t nread)
{
    LOG(LOG_DEBUG) << "_Enqueue";

    if (stream->GetDataHandler())
    {
        stream->GetDataHandler()(buf, nread);
    }
}

} // namespace translayor
