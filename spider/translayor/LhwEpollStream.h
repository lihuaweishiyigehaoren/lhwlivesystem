/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEPollStream.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwEpollStream epoll数据流操作器
 * @desc:作用: 负责客户端事件之间的传输IO传输,是clietn和connecter的基类
 */

#pragma once

#include "LhwLinuxEpoll.h"
#include "LhwBaseStream.h"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

namespace translayor
{
    class LhwEpollStream : public LhwBaseStream
    {
    public:
        LhwEpollStream(NativeSocket nativeSocket) : 
            LhwBaseStream(nativeSocket) {}

        virtual ~LhwEpollStream() {}

        LhwEpollStream(const LhwEpollStream& stream) = delete;

        /*
        * 从套接字读取数据
        * @param buffer 缓冲区
        * @param bufferSize 待接收的字节数
        * @param readSize 读取大小
        */
        virtual int32_t receiveData(char* buffer, int32_t bufferSize, int32_t& readSize) override;

        /*
        * 从套接字发送数据
        * @param byteArray 字符数组
        */
        virtual int32_t sendData(const LhwByteArray& byteArray) override;

        uint32_t getEvent() const
        {
            return _events;
        }

        void setEvents(uint32_t events)
        {
            _events = events;
        }

        void onData(DataHandler handler) override
        {
            _dataHandler = handler;
        }

        DataHandler getDataHandler() override
        {
            return _dataHandler;
        }

    private:
        uint32_t _events; // 加入epoll的事件属性
        DataHandler _dataHandler; // 初始化为了PackageDataSink中Write()函数
    };

    typedef std::shared_ptr <LhwEpollStream> EPollStreamPtr;
}