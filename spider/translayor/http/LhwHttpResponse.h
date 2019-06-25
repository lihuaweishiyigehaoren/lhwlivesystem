/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEpollLoop.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwHttpResponse 用于对消息的响应
 * @desc:作用:主要是将对象转换为字符串
 */


#pragma once

#include "LhwHttpContext.h"

namespace translayor 
{
    class LhwHttpResponse : public LhwHttpContext 
    {
    public:
        LhwHttpResponse() {}
        virtual std::string toStdString() const override;

        int32_t getStatusCode() const 
        {
            return _statusCode;
        }

        void setStatusCode(int32_t statusCode) 
        {
            _statusCode = statusCode;
        }

        const std::string& getStatusMessage() const 
        {
            return _statusMessage;
        }

        void setStatusMessage(const std::string& message) 
        {
            _statusMessage = message;
        }

    private:
        std::string getResponseLine() const;

        int32_t _statusCode; // 状态代码
        std::string _statusMessage;

        /*
        * 结构
        * 状态行: HTTP/1.1 200k
        * 消息头: Server: SimpleWebServer
        *        Content-type: text/html
        *        Content-length: 2048
        *        .......
        * 消息体: <html>
        *        .......
        *        <body>
        *        .......
        *        <html>
        */
    };
}