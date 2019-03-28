

#include "EPollClient.h"
#include "CommonUtils.h"
#include "EPollLoop.h"
#include "Logging.h"

#include <unistd.h>

namespace translayor {
    void EPollClient::Connect(const std::string& host, int32_t port) {
        struct sockaddr_in serv_addr;

        bzero((char*)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
        serv_addr.sin_port = htons(port);

        translayor::SetNonBlocking(GetNativeSocket());

        connect(GetNativeSocket(), (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        std::cout << errno <<std::endl;

    }

    EPollClientPtr EPollClient::Connect(const std::string& ip, int32_t port, DataSink* dataSink) {
        int32_t clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        // Connect
        EPollClientPtr client = EPollClientPtr(new EPollClient(clientSocket));
        client->SetDataSink(dataSink);
        client->Connect(ip, port);

        // TODO: Add to epoll loop
        EPollLoop* ePollLoop = EPollLoop::Get();

        client->_events = EPOLLIN | EPOLLET;
        if ( ePollLoop->AddEpollEvents(client->_events, clientSocket) == -1 ) {
            perror("epoll_ctl: add");
            exit(EXIT_FAILURE);
        }

        ePollLoop->AddStream(client);

        return client;
    }

    int32_t EPollClient::Receive(char* buffer, int32_t bufferSize, int32_t& readSize) {
        readSize = 0;
        int32_t nread = 0;
        NativeSocketEvent ev;

        while ((nread = read(GetNativeSocket(), buffer + readSize, bufferSize - 1)) > 0) {
            readSize += nread;
        }

        return nread;
    }

    int32_t EPollClient::Send(const translayor::ByteArray& byteArray) {
        LOG(LOG_DEBUG) << "EPollConnection::Send";

        struct epoll_event ev;
        NativeSocket clientSocket = GetNativeSocket();

        if ( EPollLoop::Get()->ModifyEpollEvents(_events | EPOLLOUT, clientSocket) ) {
            // TODO: MARK ERASE
            LOG(LOG_ERROR) << "FATAL epoll_ctl: mod failed!";
        }

        const char* buf = byteArray.data();
        int32_t size = byteArray.size();
        int32_t n = size;

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
