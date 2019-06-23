/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwSocket.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * Socket 套接字基类,便于存储套接字
 */


#pragma once

#include "LhwLinuxEpoll.h"

#include <unistd.h>

namespace translayor
{
    class Socket 
    {
    public:
        Socket() : _socket(0) {}
        Socket(NativeSocket nativeSocket) : _socket(nativeSocket){}

        virtual ~Socket()
        {
            close(_socket);
        }

        NativeSocket getSocket() const
        {
            return _socket;
        }

        void setSocket(NativeSocket thisSocket)
        {
            _socket = thisSocket;
        }

    private:
        NativeSocket _socket;
    };
} // namespace translayor
