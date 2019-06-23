/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwBaseServer.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * BasicServer 该类是服务器的基类,定义一系列纯虚函数接口
 * @desc:作用: 连接函数,回调函数接口
 */

#pragma once

#include "LhwSocket.h"
#include "LhwIOStream.h"

#include <functional>

namespace translayor
{
    template<class ConnectionType>
    class BasicServer : public Socket
    {
    public:
        typedef std::function<void(IOStream* stream)> ConnectHandler;
        typedef std::function<void(IOStream* stream)> DisconnectHandler;

        BasicServer() {}

        virtual int32_t startBindListen(const std::string& host, int32_t port, int32_t backlog)=0;
        virtual void onConnect(ConnectHandler handler)=0;
        virtual void onDisconnect(DisconnectHandler handler)=0;

        virtual ConnectionType acceptClientOfServer(int32_t listenfd)=0;
    };
} // namespace translayor
