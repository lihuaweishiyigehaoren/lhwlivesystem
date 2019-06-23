#include "LhwHttpConnection.h"
#include "../LhwByteArray.h"
#include "Logging.h"

#include <iostream>

namespace translayor {
    LhwHttpConnection::LhwHttpConnection(Connection* connection) :
            _connection(connection) {
        LOG(LOG_DEBUG) << _connection ;
        auto tcpDataHandler = std::bind(&LhwHttpConnection::handleData, this, std::placeholders::_1, std::placeholders::_2);
        _connection->onData(tcpDataHandler); // jiang TcpConnection的OnDataIndication事件绑定到HandleData成员函数
    }

    int32_t LhwHttpConnection::handleData(const char* buffer, int64_t size) 
    {
        LOG(LOG_DEBUG) << buffer ;
        LOG(LOG_DEBUG) << size ;
        std::string requestText(buffer, size);

        _request.parseStdString(requestText);

        if ( _requstHandler ) 
        {
            _requstHandler(_request);
        }

        if ( _dataHandler && _request.getContent().size() > 0 ) 
        {
            _dataHandler(_request.getContent());
        }

        return 0;
    }

    void LhwHttpConnection::sendResponse(const LhwHttpResponse& response) 
    {
        _response = response;

        _connection->sendData(LhwByteArray(_response.toStdString()));
    }
}
