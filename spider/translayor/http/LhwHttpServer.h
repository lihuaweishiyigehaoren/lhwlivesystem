#pragma once

#include "../LhwComponAlias.h"
#include "LhwHttpConnection.h"
#include <vector>
#include <functional>

namespace  translayor 
{
    class IoLoop;

    class LhwHttpServer 
    {
    public:
        typedef std::function<void(LhwHttpConnection* connection)> ConnectionHandler;

        LhwHttpServer();
        virtual ~LhwHttpServer();

        void Listen(const std::string& host, int32_t port, int32_t backlog = 20);
        void OnConnection(ConnectionHandler handler) 
        {
            _connectionHandler = handler;
        }

    private:
        Server _server;
        ConnectionHandler _connectionHandler;
    };

}