#include "LhwEpollStream.h"
#include "LhwEpollLoop.h"
#include "Logging.h"
#include "LhwByteArray.h"

#include <unistd.h>

namespace translayor
{
    int32_t LhwEpollStream::receiveData(char* buffer, int32_t bufferSize, int32_t& readSize)
    {
        readSize = 0;
        int32_t nread = 0;
        // NativeSocketEvent ev;

        // 这里用了read,后期换成linux的recv函数比较好
        while((nread = read(getSocket(),buffer + readSize,bufferSize-readSize)) > 0) // bufferSize-1指定可以接收的最大字节数
        {
            readSize += nread;
        }

        // 修改事件
        LhwEpollLoop::Get()->modifyEpollEvents(_events | EPOLLOUT,getSocket());

        return nread; 
    }

    int32_t LhwEpollStream::sendData(const translayor::LhwByteArray& byteArray)
    {
        LOG(LOG_DEBUG) << "Connectioner::SendData";

        struct epoll_event ev;
        NativeSocket clientSocket = getSocket();

        // EPOLLOUT 所指的意思是:输出缓冲为空,可以立即发送数据的情况
        // if (LhwEpollLoop::Get()->modifyEpollEvents(_events | EPOLLOUT, clientSocket))
        // {
        //     LOG(LOG_ERROR) << "epoll_ctl: mod failed!";
        // }
        
        const char* buf = byteArray.data();

        LOG(LOG_DEBUG) << byteArray.size();
        
        int32_t size = byteArray.size();
        int32_t n = size;

        int32_t nwrite = 0;
        while(n > 0)
        {
            nwrite = write(clientSocket, buf + size - n, n);
            if(nwrite < n)
            {
                if(nwrite == -1 && errno != EAGAIN)
                {
                    LOG(LOG_ERROR) << "write data to peer failed!";
                }
                break;
            }

            n -= nwrite;
        }

        LhwEpollLoop::Get()->modifyEpollEvents(EPOLLIN | EPOLLET,clientSocket);
        return nwrite;
    }

    void LhwEpollStream::postDataToBuffer(const std::string &data)
    {
        std::lock_guard<std::mutex> locker(_mutex);
        _buffers.push(data); 
    }
}