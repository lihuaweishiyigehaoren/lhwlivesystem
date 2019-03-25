#include "../TransLayor.h"
#include "HttpConnection.h"
#include "../ByteArray.h"
#include "Logging.h"

#include <iostream>

namespace translayor {
    HttpConnection::HttpConnection(TcpConnection* connection) :
            _connection(connection) {
        LOG(LOG_DEBUG) << _connection ;
        auto tcpDataHandler = std::bind(&HttpConnection::HandleData, this, std::placeholders::_1, std::placeholders::_2);
        _connection->OnData(tcpDataHandler); // jiang TcpConnection的OnDataIndication事件绑定到HandleData成员函数
    }

    int32_t HttpConnection::HandleData(const char* buffer, int64_t size) {
        LOG(LOG_DEBUG) << buffer ;
        LOG(LOG_DEBUG) << size ;
        std::string requestText(buffer, size);

        _request.ParseStdString(requestText);

        if ( _requstHandler ) {
            _requstHandler(_request);
        }

        if ( _dataHandler && _request.GetContent().size() > 0 ) {
            _dataHandler(_request.GetContent());
        }

        return 0;
    }

    void HttpConnection::SendResponse(const HttpResponse& response) {
        _response = response;

        _connection->Send(ByteArray(_response.ToStdString()));
    }
}
