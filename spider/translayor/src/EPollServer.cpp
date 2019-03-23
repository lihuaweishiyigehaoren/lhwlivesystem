#include "EPollServer.h"
#include "EPollLoop.h"
#include "CommonUtils.h"
#include "Logging.h"

#include <cstdint>
#include <cassert>
#include <EPollLoop.h>

#ifndef DISABLE_ASSERT
#ifdef assert
#undef assert
#endif

#define assert(x)
#endif

namespace translayor
{
    int32_t EPollServer::_Bind(const std::string& host, int32_t port)
    {
        int32_t listenfd;
        if((listenfd == socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            LOG(LOG_ERROR) << "Create socket failed!";
            exit(1);
        }

        SetNativeSocket(listenfd);
        int32_t option = 1;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        translayor::SetNonBlocking(listenfd);

        NativeSocketAddress addr;
        bzero(&addr,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        add.sin_addr.s_addr = inet_addr(host.c_str());

        int32_t errorCode = bind(listenfd,(struct sockaddr*)& addr,sizeof(addr));
        if (errorCode < 0)
        {
            LOG(LOG_ERROR) << "Bind socket failed!";
            assert(0);
            return errorCode;
        }

        return 0;
    }

    int32_t EPollServer::Listen(const std::string& host, int32_t port, int32_t backlog)
    {
        _Bind(host,port);

        int32_t listenfd = GetNativeSocket();

        int32_t errorCode = listen(listenfd,backlog);

        if(-1 == errorCode)
        {
            LOG(LOG_ERROR) << "Listen socket failed";
            assert(0);
            return errorCode;
        }

        errorCode = EPollLoop::Get()->AddEpollEvents(EPOLLIN, listenfd);

        if(errorCode == -1)
        {
            LOG(LOG_ERROR) << "FATAL epoll_ctl: listen_sock!";
            assert(0);
            return errorCode;
        }

        EPollLoop::Get()->AddServer(listenfd, this);
    }

    EPollConnectionPtr EPollServer::Accept(int32_t sockfd)
    {
        int32_t conn_sock = 0;
        int32_t addrlen = 0;
        int32_t remote = 0;

        int32_t listenfd = GetNativeSocket();
        while((conn_sock = accept(listenfd,(struct sockaddr*)& remote, (socklen_t*)& addrlen))>0)
        {
            translayor::SetNonBlocking(conn_sock);

            NativeSocketEvent ev;
            ev.events = EPOLLIN | EPOLLET;
            ev.data.fd = conn_sock;

            if (epoll_ctl(sockfd, EPOLL_CTL_ADD,conn_sock,&ev) == -1)
            {
                perror("epoll_ctl: add");
                exit(EXIT_FAILURE);
            }

            EPollConnectionPtr connection = std::make_shared<EPollConnection>(conn_sock);
            if (_connectHandler)
            {
                _connectHandler(connection.get());
            }

            return connection;
        }

        if (conn_sock == -1)
        {
            if (errno != EAGAIN && errno != ECONNABORTED 
            && errno != EPROTO && errno != EINTR)
            {
                perror("accept");
            }
        }

        return EPollConnectionPtr(nullptr);
        
    }
}

