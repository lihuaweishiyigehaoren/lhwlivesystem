#include "LhwHttpServer.h"
#include "LhwHttpConnection.h"
#include "../PackageDataSink.h"

namespace  translayor {
    LhwHttpServer::LhwHttpServer() 
    {

    }

    LhwHttpServer::~LhwHttpServer() 
    {

    }

    void LhwHttpServer::Listen(const std::string& host, int32_t port, int32_t backlog) 
    {
        _server.startBindListen(host, port, backlog);

        _server.onConnect([this](IOStream* stream) 
        {
            Connection* connection = dynamic_cast<Connection*>(stream);
            LhwHttpConnection* httpConnection = new LhwHttpConnection(connection);
            if ( _connectionHandler ) 
            {
                _connectionHandler(httpConnection);
            }
        });
    }
}
