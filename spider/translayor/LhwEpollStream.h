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
#include "LhwByteArray.h"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
// #include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

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

        uint32_t getEvent()
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

        /*
        * 将数据加入到输出缓存
        * @para event 事件
        */
        virtual void postDataToBuffer(const std::string &data) override;

        /*
        * 从输出缓存中获取容器
        */
        std::string getDataFromBuffer()
        {
            std::unique_lock<std::mutex> locker(_mutex);

            if(_buffers.empty())
            {
                // return std::string("");
                _waitCondition.wait_for(locker,std::chrono::microseconds(5));

            }

            if(!_buffers.empty())
            {
                std::string data = _buffers.front();
                _buffers.pop();

                return data;
            }

            return std::string("");
        }

    private:
        uint32_t _events; // 加入epoll的事件属性
        DataHandler _dataHandler; // 初始化为了PackageDataSink中Write()函数

        // 使用缓存
        std::mutex _mutex;
        std::condition_variable _waitCondition;
        std::queue<std::string> _buffers;
    };

    typedef std::shared_ptr <LhwEpollStream> EPollStreamPtr;
}