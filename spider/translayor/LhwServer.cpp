#include "LhwServer.h"
#include "LhwEpollLoop.h"
#include "LhwCommon.h"
#include "Logging.h"

#include <cstdint>
#include <cassert>

#ifndef DISABLE_ASSERT
#ifdef assert
#undef assert
#endif

#define assert(x)
#endif

namespace translayor
{
int32_t LhwServer::_bind(const std::string &host, int32_t port)
{
    // 创建服务器套接字,一个服务器仅创建一次
    int32_t listenfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        LOG(LOG_ERROR) << "create server socket failed!";
        exit(1);
    }

    setSocket(listenfd); // 设置该server端的套接字,便于访问
    // 设置套接字属性,SO_REUSEADDR可以时服务器进入time-wait状态的时候进行地址再分配,那么就可以立马连上现在的地址
    int32_t option = 1;
    int opt = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));// 详解https://baike.baidu.com/item/setsockopt/10069288?fr=aladdin
    if( opt == -1 )
    {
        LOG(LOG_ERROR) << "setsockopt reuseaddr pro failed";
    }

    // 将服务器套接字设置为非阻塞的,边缘触发必须设置为非阻塞
    translayor::SetNonBlocking(listenfd); 

    NativeSocketAddress addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host.c_str());

    int32_t errorCode = bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    if (errorCode < 0)
    {
        LOG(LOG_ERROR) << errno;
        LOG(LOG_ERROR) << "bind socket failed!";
        assert(0);
        return errorCode;
    }

    return 0;
}

int32_t LhwServer::startBindListen(const std::string &host, int32_t port, int32_t backlog)
{
    _bind(host, port); // 创建并绑定到套接字地址

    int32_t listenfd = getSocket(); // 获取创建的套接字对象

    // 服务套接字用来监听连接来的客户端,一次最多监控backlog个
    int32_t errorCode = listen(listenfd, backlog);
    if (-1 == errorCode)
    {
        LOG(LOG_ERROR) << "server listen failed";
        assert(0);
        return errorCode;
    }

    // 将服务器套接字加入到监听列表中 EPOLLIN属于条件触发
    errorCode = LhwEpollLoop::Get()->addEpollEvents(EPOLLIN, listenfd);

    if (errorCode == -1)
    {
        LOG(LOG_ERROR) << "epoll_ctl server socket fail";
        assert(0);
        return errorCode;
    }

    // 加入该键值对
    LhwEpollLoop::Get()->addFdToServer(listenfd, this);
}

Collectioner LhwServer::acceptClientOfServer(int32_t sockfd)
{
    int32_t conn_sock = 0;
    int32_t addrlen = 0;
    int32_t remote = 0;

    int32_t listenfd = getSocket();
    while ((conn_sock = accept(listenfd, (struct sockaddr *)&remote, (socklen_t *)&addrlen)) > 0)
    {

        LOG(LOG_DEBUG) << "accept";

        // 设置客户端套接字非阻塞
        translayor::SetNonBlocking(conn_sock);

        NativeSocketEvent ev;
        ev.events = EPOLLIN | EPOLLET; // 设置为边缘触发模式
        ev.data.fd = conn_sock;

        if (epoll_ctl(sockfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1)
        {
            perror("epoll_ctl: add");
            exit(EXIT_FAILURE);
        }

        // 建立对客户端套接字的连接对象connecter
        Collectioner connection = std::make_shared<LhwClientConnected>(conn_sock);
        LOG(LOG_DEBUG) << "acceptconnection";
        
        // 通过main中初始化的回调函数,再次调用回调函数
        if (_connectHandler)
        {
            LOG(LOG_DEBUG) << "connectHandler exist";
            _connectHandler(connection.get());
        }

        return connection;
    }

    if (conn_sock == -1)
    {
        // 自查
        if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
        {
            perror("accept");
        }
    }

    return Collectioner(nullptr);
}
} 
