#pragma once

#include "Loop.h"
#include "EPollConnection.h"
#include "EPollStream.h"
#include "EPollServer.h"
#include "EPollClient.h"
#include "Net.h"
#include "DataSink.h"
#include "NetLinux.h"
#include "Common.h"

#include <map>
#include <memory>
#include <thread>
#include <string>

#include <sys/epoll.h>


namespace translayor {

    class EventQueue;

    class EPollServer;

    class EPollLoop : public Loop {
    public:
        static EPollLoop* Get();

        virtual ~EPollLoop() override;

        void AddServer(NativeSocket socket, EPollServer* server);
        void AddStream(EPollStreamPtr stream);

        int32_t AddEpollEvents(int32_t events, int32_t fd);
        int32_t ModifyEpollEvents(int32_t events, int32_t fd);

    protected:
        EPollLoop();// 构造函数搞成私有的,是因为采用了单利模式,外部仅有一个实例

        virtual void _Run() override;

    private:
        void _Initialize();

        void _EPollThread();

        void _HandleEvent(int32_t eventfd, struct epoll_event* events, int32_t nfds);

        int32_t _Accept(int32_t eventfd, int32_t listenfd);

        void _Read(int32_t eventfd, int32_t fd, uint32_t events);

        void _Enqueue(EPollStreamPtr connection, const char* buf, int64_t nread);

    private:
        int32_t _eventfd; // epoll文件描述符
        bool _shutdown; // 表示是否关机

        std::map<NativeSocket, EPollServer*> _servers; // 存储套接字和服务器之间的关系,容易通过套接字找出其对应的服务器
        std::map <NativeSocket, EPollStreamPtr> _streams; // 同一管理所有的流,便于使用套接字寻找对应的流对象
    };
}
