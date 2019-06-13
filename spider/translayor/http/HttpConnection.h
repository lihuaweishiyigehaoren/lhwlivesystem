#pragma once
#include "../TransLayor.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <functional>

namespace translayor {
    class HttpConnection {
    public:
        typedef std::function<void(const HttpRequest& request)> RequestHandler; // 请求到来时的回调函数
        typedef std::function<void(const std::string& data)> DataHandler; // 数据到来的回调函数

        HttpConnection(TcpConnection* connection);

        int32_t HandleData(const char* buffer, int64_t size);// 负责处理TCP连接的数据时间,将其翻译成HTTP消息

        // 数据处理回调函数设置器
        void OnData(DataHandler dataHandler) {
            _dataHandler = dataHandler;
        }

        void OnRequest(RequestHandler requestHandler) {
            _requstHandler = requestHandler;
        }

        // 发送HTTP响应
        void SendResponse(const HttpResponse& response);

    private:
        TcpConnection* _connection;
        HttpRequest _request;
        HttpResponse _response;
        DataHandler _dataHandler;
        RequestHandler _requstHandler;
    };
}