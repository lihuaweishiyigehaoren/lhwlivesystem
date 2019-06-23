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
 * LhwBaseStream 基础数据流,同时可以存储与数据流对应的套接字以便操作
 * @desc:作用: 设置与套接字相关的数据流操作,继承IStream,便于流操作,同事实现了DataSink的设置获取接口
 */

#pragma once

#include "LhwSocket.h"
#include "LhwIOStream.h"

#include <memory>

namespace translayor
{
    class DataSink;

    // 基本的数据流类
    class LhwBaseStream : public IOStream, public Socket
    {
    public:
        LhwBaseStream() = default;

        // 如果用户指定了套接字,将在该套接字的基础上建立数据流
        LhwBaseStream(NativeSocket nativeSocket) : 
        Socket(nativeSocket) 
        {

        }

        LhwBaseStream(const LhwBaseStream & stream) = delete;

        // 设置数据收集器
        virtual void SetDataSink(DataSink* dataSink)
        {
            _dataSink = dataSink;
        }

        virtual DataSink* GetDataSink()
        {
            return _dataSink;
        }

        virtual const DataSink* GetDataSink() const
        {
            return _dataSink;
        }

    private:
        DataSink* _dataSink; // 数据接收,可以传输数据到外部
    };
}