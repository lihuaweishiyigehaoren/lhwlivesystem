/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file DataSink.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * DataSink 通用的数据接收层
 * @desc:作用: 当传输层接收到数据后,会通过用户定义的DataSink对象传输到外部
 */

#pragma once

#include "LhwIOStream.h"

#include <cstdint>
#include <functional>

namespace translayor
{
    class DataSink
    {
    public:
        virtual int32_t Write(IOStream* stream, const char* buf, int64_t bytes)=0;
        IOStream::DataHandler StreamDataHandler(IOStream* stream)
        {
            return std::bind(&DataSink::Write,this,stream,std::placeholders::_1,std::placeholders::_2);
        }
    };
}