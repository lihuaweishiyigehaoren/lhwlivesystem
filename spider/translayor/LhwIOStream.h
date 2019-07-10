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
 * IOStream 通用数据流层
 * @desc:作用: 代表所有可以读/写的字节流的接口
 */

#pragma once

#include "LhwByteArray.h"
#include <functional>
#include <string>

#include "LhwUser.h"

namespace translayor
{
    class IOStream 
    {

    public:
        typedef std::function<int32_t(User buf,int64_t size)> DataHandler;

        // 接收时候设置一个接收缓冲区
        virtual int32_t receiveData(char* buffer,int32_t bufferSize,int32_t& readSize)=0;
        virtual int32_t sendData(const LhwByteArray & LhwByteArray)=0;

        virtual void dataProcess(User &user) = 0;

        // 投递数据到输出缓冲区
        virtual void postDataToBuffer(const User &data) = 0;
    
        virtual void onData(DataHandler handler)=0;
        virtual DataHandler getDataHandler()=0;
    
    };
} // namespace translayor
