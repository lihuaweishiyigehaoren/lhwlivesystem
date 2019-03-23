#pragma once

#include "Net.h"
#include "PackageDataSink.h"
#include "EPollConnection.h"

namespace translayor
{
    class EPollServer : public BasicServer<EPollConnectionPtr>
    {
    public:
        EPollServer();
        virtual ~EPollServer();

        int32_t Listen(const std::string& host, int32_t port, int32_t backlog = 20) override;

        void OnConnect(ConnectHandler handler)
        {
            _connectHandler = handler;
        }

        void OnDisconnect(DisconnectHandler handler)
        {
            _disconnectIndication = handler;
        }

        EPollConnectionPtr Accept(int32_t sockfd);

    private:
        int32_t _Bind(const std::string& host, int32_t port);

        DataSink * _dataSink;
        ConnectHandler _connectHandler;
        DisconnectHandler _disconnectIndication;
    };
    
}