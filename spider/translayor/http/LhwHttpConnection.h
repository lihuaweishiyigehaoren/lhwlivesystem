/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwHttpConnection.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwHttpConnection http连接
 * @desc:作用: 负责接受请求并发送响应
 */

#pragma once
#include "../LhwComponAlias.h"
#include "LhwHttpRequest.h"
#include "LhwHttpResponse.h"
#include <functional>

namespace translayor 
{
    class LhwHttpConnection 
    {
    public:
        typedef std::function<void(const LhwHttpRequest& request)> RequestHandler; // 请求到来时的回调函数
        typedef std::function<void(const std::string& data)> DataHandler; // 数据到来的回调函数

        LhwHttpConnection(Client * connection);

        int32_t handleData(User buffer, int64_t size);// 负责处理TCP连接的数据时间,将其翻译成HTTP消息

        // 数据处理回调函数设置器
        void onData(DataHandler dataHandler) 
        {
            _dataHandler = dataHandler;
        }

        void onRequest(RequestHandler requestHandler) 
        {
            _requstHandler = requestHandler;
        }

        // 发送HTTP响应
        void sendResponse(const LhwHttpResponse& response);

    private:
        Client* _connection;
        LhwHttpRequest _request;
        LhwHttpResponse _response;
        DataHandler _dataHandler;
        RequestHandler _requstHandler;
    };
}