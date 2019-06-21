

#include "EPollClient.h"
#include "CommonUtils.h"
#include "LhwEpollLoop.h"
#include "Logging.h"

#include <unistd.h>

namespace translayor {

    // 该函数负责向服务器发起连接
    void EPollClient::Connect(const std::string& host, int32_t port) 
    {
        struct sockaddr_in serv_addr;

        bzero((char*)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
        serv_addr.sin_port = htons(port);

        translayor::SetNonBlocking(GetNativeSocket());

        connect(GetNativeSocket(), (struct sockaddr*)&serv_addr, sizeof(serv_addr));

        std::cout << errno <<std::endl;

    }
    // 静态函数,参数dataSink,表示数据到来时的回调函数
    EPollClientPtr EPollClient::Connect(const std::string& ip, int32_t port, DataSink* dataSink) 
    {
        int32_t clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        // Connect
        EPollClientPtr client = EPollClientPtr(new EPollClient(clientSocket));
        client->SetDataSink(dataSink); // 将数据收集器赋予客户端
        client->Connect(ip, port);

        // 添加事件循环
        LhwEpollLoop* ePollLoop = LhwEpollLoop::Get();

        client->_events = EPOLLIN | EPOLLET;
        if ( ePollLoop->addEpollEvents(client->_events, clientSocket) == -1 ) // 将新创建的客户端套接字
        {
            perror("epoll_ctl: add");
            exit(EXIT_FAILURE);
        }

        ePollLoop->AddStream(client);

        return client;
    }

    // 接收事件,不断从连接套接字中读取数据,直到nread小于等于0为止
    int32_t EPollClient::Receive(char* buffer, int32_t bufferSize, int32_t& readSize) 
    {
        readSize = 0;
        int32_t nread = 0;
        NativeSocketEvent ev;

        while ((nread = read(GetNativeSocket(), buffer + readSize, bufferSize - 1)) > 0) {
            readSize += nread;
        }

        return nread;
    }

    // 发送事件
    int32_t EPollClient::Send(const translayor::ByteArray& byteArray) 
    {
        LOG(LOG_DEBUG) << "EPollConnection::Send";

        struct epoll_event ev;
        NativeSocket clientSocket = GetNativeSocket();

        if ( LhwEpollLoop::Get()->modifyEpollEvents(_events | EPOLLOUT, clientSocket) ) // 为客户端加上EPOLLOUT的事件监听.-表示对应的文件描述符可以写
        {
            LOG(LOG_ERROR) << "FATAL epoll_ctl: mod failed!";
        }

        const char* buf = byteArray.data();
        int32_t size = byteArray.size();
        int32_t n = size;

        // 循环分组将用户发送的字节数组中的数据发送出去,直到发送的字节数为0为止
        while (n > 0) {
            int32_t nwrite;
            nwrite = write(clientSocket, buf + size - n, n);
            if (nwrite < n) {
                if (nwrite == -1 && errno != EAGAIN) {
                    LOG(LOG_ERROR) << "FATAL write data to peer failed!";
                }
                break;
            }
            n -= nwrite;
        }

        return 0;
    }
}
