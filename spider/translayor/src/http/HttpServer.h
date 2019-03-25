#pragma once

#include "../TransLayor.h"
#include "HttpConnection.h"
#include <vector>
#include <functional>

namespace  translayor 
{
    class IoLoop;

    class HttpServer 
    {
    public:
        typedef std::function<void(HttpConnection* connection)> ConnectionHandler;

        HttpServer();
        virtual ~HttpServer();

        void Listen(const std::string& host, int32_t port, int32_t backlog = 20);
        void OnConnection(ConnectionHandler handler) {
            _connectionHandler = handler;
        }

    private:
        TcpServer _server;
        ConnectionHandler _connectionHandler;
    };

}