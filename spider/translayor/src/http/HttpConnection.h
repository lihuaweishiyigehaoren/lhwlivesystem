#pragma once
#include "../TransLayor.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <functional>

namespace translayor {
    class HttpConnection {
    public:
        typedef std::function<void(const HttpRequest& request)> RequestHandler;
        typedef std::function<void(const std::string& data)> DataHandler;

        HttpConnection(TcpConnection* connection);

        int32_t HandleData(const char* buffer, int64_t size);

        void OnData(DataHandler dataHandler) {
            _dataHandler = dataHandler;
        }

        void OnRequest(RequestHandler requestHandler) {
            _requstHandler = requestHandler;
        }

        void SendResponse(const HttpResponse& response);

    private:
        TcpConnection* _connection;
        HttpRequest _request;
        HttpResponse _response;
        DataHandler _dataHandler;
        RequestHandler _requstHandler;
    };
}