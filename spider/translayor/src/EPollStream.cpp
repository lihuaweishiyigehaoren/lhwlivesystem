#include "EPollStream.h"

#include "EPollStream.h"
#include "EPollLoop.h"
#include "Logging.h"
#include "ByteArray.h"

#include <unistd.h>

namespace translayor
{
    int32_t EPollStream::Receive(char* buffer, int32_t bufferSize, int32_t& readSize)
    {
        readSize = 0;
        int32_t nread = 0;
        NativeSocketEvent ev;

        while((nread = read(GetNativeSocket(),buffer + readSize,bufferSize-1)) > 0)
        {
            readSize += nread;
        }

        return nread; 
    }

    /*
    *首先滴啊用GetN获取数据流的套接字,然后修改epoll监听事件,接着从字节数组获取缓冲区和长度,并分批写入套接字
    */
    int32_t EPollStream::Send(const translayor::ByteArray& byteArray)
    {
        LOG(LOG_DEBUG) << "EPollConnection::Send";

        struct epoll_event ev;
        NativeSocket clienSocket = GetNativeSocket();

        if (EPollLoop::Get()->ModifyEpollEvents(_events | EPOLLOUT, clientSocket))
        {
            LOG(LOG_ERROR) << "FATAL epoll_ctl: mod failed!";
        }
        
        const char* buf = byteArray.data();
        int32_t size = byteArray.size();
        int32_t n = size;

        while(n > 0)
        {
            int32_t nwrite;
            nwrite = write(clientSocket, buf + size - n, n)
            if(nwrite < n)
            {
                if(nwrite == -1 && errno != EAGAIN)
                {
                    LOG(LOG_ERROR) << "FATAL write data to peer failed!";
                }
                break;
            }

            n -= nwrite;
        }
        return 0;
    }
}