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
#include "LhwUser.h"

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

        /*
        * 读取服务器返回来的协议包
        */
       void onReadyRead();

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverReg(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverLogin(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverExit(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverRoomName(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverChatName(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverRoomList(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverChatList(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverChatText(User user);

        /*
        * 服务器套接字连接客户端
        * @param sockfd epoll_create创建的侦听套接字
        */
        void serverQuit(User user);

    private:
        LhwClient(NativeSocket clientSocket) :
                LhwEpollStream(clientSocket){
            this->setSocket(clientSocket);
        }

    private:
        uint32_t _events;

        static std::mutex _mutex1;
        static std::mutex _mutex2;
    };
}