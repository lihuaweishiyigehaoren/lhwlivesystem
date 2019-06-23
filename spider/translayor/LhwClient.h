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
 * LhwClient 客户端
 * @desc:作用: 设计客户端的各种接口
 */

#pragma once

#include "LhwEpollStream.h"
#include "DataSink.h"

#include <memory>

namespace translayor 
{
    class LhwClient;
    typedef std::shared_ptr<LhwClient> EPollClientPtr;

    class LhwClient : public LhwEpollStream // 是一个可以主动发起连接的数据流
    {
    public:
        LhwClient(const LhwClient& client) = delete;
        virtual ~LhwClient() { }

        virtual int32_t receiveData(char* buffer, int32_t bufferSize, int32_t& readSize) override;
        virtual int32_t sendData(const LhwByteArray & byteArray) override;

        uint32_t getEvents() const 
        {
            return _events;
        }

        void setEvents(uint32_t events)
        {
            _events = events;
        }

        void connect(const std::string& host, int32_t port);
        static EPollClientPtr connect(const std::string& ip, int32_t port, DataSink* dataSink);

    private:
        LhwClient(NativeSocket clientSocket) :
                LhwEpollStream(clientSocket){
            this->setSocket(clientSocket);
        }

    private:
        uint32_t _events;
    };
}