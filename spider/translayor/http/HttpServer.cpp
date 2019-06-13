

#include "HttpServer.h"
#include "HttpConnection.h"
#include "../PackageDataSink.h"

namespace  translayor {
    HttpServer::HttpServer() {
    }

    HttpServer::~HttpServer() {
    }

    void HttpServer::Listen(const std::string& host, int32_t port, int32_t backlog) {
        _server.Listen(host, port, backlog);

        _server.OnConnect([this](IStream* stream) {
            TcpConnection* connection = dynamic_cast<TcpConnection*>(stream);
            HttpConnection* httpConnection = new HttpConnection(connection);
            if ( _connectionHandler ) {
                _connectionHandler(httpConnection);
            }
        });
    }
}
