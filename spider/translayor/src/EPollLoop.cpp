/**
 *auther: HuaWeiLi
 *作用:epoll的事件循环类,负责不断的监听来自epoll的事件,并对事件进行处理
 */

#include "EPollLoop.h"
#include "Logging.h"

#include <signal.h>
#include <cassert>

namespace translayor {
    using namespace std::placeholders;

    /*
    *静态函数,用于获取EPoolLoop对象的唯一实例
    * */
    EPollLoop* EPollLoop::Get()
    {
        static EPollLoop epollLoop;
        return &epollLoop;
    }

    EPollLoop::EPollLoop()
    // _shutdown(false)
    {
        LOG(LOG_DEBUG) << "EPollLoop::EPollLoop";

        sigset_t set; // 设置进程信号
        sigemptyset(&set); // 清空进程信号设置
        sigaddset(&set, SIGPIPE); 
        sigprocmask(SIG_BLOCK, &set, NULL);

        _Initialize();
    }

    EPollLoop::~EPollLoop()
    {
        _shutdown = true;
    }
    
    /*
    *在事件循环中监听socket套接字并将触发的消息转发给server
    *para:para1 服务器的套接字, para2 EPool服务器的对象指针
    **/
    void EPollLoop::AddServer(NativeSocket socket, EPollServer* server)
    {
        _servers.insert({socket, server});
    }

    /*
    *将一个流对象的指针添加到Loop中,这样Loop会帮助流对象监听输入与输出事件,一旦有输入输出到来会通过回调函数通知流对象
    **/
    void EPollLoop::AddStream(EPollStreamPtr stream)
    {
        _streams[stream->GetNativeSocket()] = stream;
    }

    /*
    *在Loop中添加一个Epoll事件,是对epoll_ctl的简单封装
    */
    int32_t EPollLoop::AddEpollEvents(int32_t events, int32_t fd)
    {
        NativeSocketEvent ev;
        ev.events = events;
        ev.data.fd = fd;

        return epoll_ctl(_eventfd, EPOLL_CTL_ADD, fd, &ev);
    }

    /*
    *改变Loop中监听的Epoll事件
    */
    int32_t EPollLoop::ModifyEpollEvents(int32_t events, int32_t fd)
    {
        NativeSocketEvent ev;
        ev.events = events;
        ev.data.fd = fd;

        return epoll_ctl(_eventfd, EPOLL_CTL_MOD, fd, &ev);
    }

    /*
    *初始化EpollLoop对象,完成资源和事件的初始化
    */
    void EPollLoop::_Initialize()
    {
        _eventfd = epoll_create(MAX_EVENT_COUNT);
        if (_eventfd == -1) {
            LOG(LOG_ERROR) << "FATAL epoll_create failed!" ;
            assert(0);
        }
    }

    void EPollLoop::_Run()
    {
        auto func = std::bind(&EPollLoop::_EPollThread, this);
        std::thread listenThread(func);// 创建一个分支线程,回调到func函数
        // std::cout << listenThread.get_id() << std::endl;
        listenThread.detach(); // 将子线程从主线程中剥离
    }

    /*
    *该函数是循环线程的主函数,整个循环都会运行在这个线程的主函数中
    */
    void EPollLoop::_EPollThread()
    {
        // 在这里_shutdown的值为0
        LOG(LOG_DEBUG) << "_EPollThread" ;
        NativeSocketEvent events[MAX_EVENT_COUNT];

        while (!_shutdown) {
            int32_t nfds;
            nfds = epoll_wait(_eventfd, events, MAX_EVENT_COUNT, -1);
            if (-1 == nfds) {
                LOG(LOG_ERROR) << "FATAL epoll_wait failed!" ;
                exit(EXIT_FAILURE);
            }

            _HandleEvent(_eventfd, events, nfds);
        }
    }

    /*
    *处理特定的Epoll事件,并对事件进行合理响应
    */
    void EPollLoop::_HandleEvent(int32_t eventfd, NativeSocketEvent* events, int32_t nfds)
    {

        for (int32_t i = 0; i < nfds; ++i) {
            int32_t fd;
            fd = events[i].data.fd;

            if (_servers.find(fd) != _servers.end()) {
                _Accept(eventfd, fd);
                continue;
            }

            int32_t n = 0;
            if (events[i].events & EPOLLIN) {
                _Read(eventfd, fd, events[i].events);
            }

            if (events[i].events & EPOLLOUT) {
            }
        }
    }

    /*
    *响应epoll中的服务器accept事件,创建与客户端的连接
    */
    int32_t EPollLoop::_Accept(int32_t eventfd, int32_t listenfd)
    {
        LOG(LOG_DEBUG) << "_Accept" ;
        EPollServer* server = _servers.find(listenfd)->second;
        EPollConnectionPtr connection = server->Accept(eventfd);

        if (connection != nullptr) {
            _streams[connection->GetNativeSocket()] = connection;
        }
    }
    
    /*
    *响应epoll中数据流的读取事件,对原始数据进行特殊处理,并通知事件所属的流对象来从流中读取数据
    */
    void EPollLoop::_Read(int32_t eventfd, int32_t fd, uint32_t events)
    {
        LOG(LOG_DEBUG) << "_Read" ;

        EPollStreamPtr stream = _streams[fd];

        char buffer[BUFSIZ];
        int32_t readSize;
        int32_t nread = stream->Receive(buffer, BUFSIZ, readSize);

        stream->SetEvents(events);

        if ((nread == -1 && errno != EAGAIN) || readSize == 0) {
            _streams.erase(fd);

            LOG(LOG_WARNING) << "errno: " << errno << ": " << strerror(errno) <<
                    ", nread: " << nread << ", n" << readSize ;
            return;
        }

        _Enqueue(stream, buffer, readSize);
    }

    /*
    *将读取到的内容发送到系统的数据读取队列中,通知数据监听方来获取处理后的数据
    */
    void EPollLoop::_Enqueue(EPollStreamPtr stream, const char* buf, int64_t nread)
    {
        LOG(LOG_DEBUG) << "_Enqueue" ;

        if ( stream->GetDataHandler() ) {
            stream->GetDataHandler()(buf, nread);
        }
    }

}
