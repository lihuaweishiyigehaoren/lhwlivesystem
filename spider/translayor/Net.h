#pragma once

#include "ByteArray.h"
#include "NetLinux.h"

#include <functional>
#include <memory>
#include <unistd.h>

namespace translayor
{
    class Socket 
    {
    public:
        Socket() : _nativeSocket(0) {}
        Socket(NativeSocket nativeSocket) : _nativeSocket(nativeSocket){}

        virtual ~Socket()
        {
            close(_nativeSocket);
        }

        NativeSocket GetNativeSocket() const
        {
            return _nativeSocket;
        }

        void SetNativeSocket(NativeSocket nativeSocket)
        {
            _nativeSocket = nativeSocket;
        }

    private:
        NativeSocket _nativeSocket;
    };


    class DataSink;

    // 数据流层:代表所有可以读/写的字节流类的接口
    class IStream {

    public:
        typedef std::function<int32_t(const char* buf,int64_t size)> DataHandler;

        /*
        *接收数据
        *para:buffer-缓冲区
        */
        virtual int32_t Receive(char* buffer,int32_t bufferSize,int32_t& readSize)=0;
        virtual int32_t Send(const ByteArray & byteArray)=0;
    
        virtual void OnData(DataHandler handler)=0;
        virtual DataHandler GetDataHandler()=0;
    
    };

    class IConnectable
    {
    public:
        virtual void Connect(const std::string & host, int32_t port) = 0;
    };

    // 基本的数据流类
    class BasicStream : public IStream, public Socket
    {
    public:
        BasicStream() = default;
        // 如果用户指定了套接字,将在该套接字的基础上建立数据流
        BasicStream(NativeSocket nativeSocket) : Socket(nativeSocket) {}
        BasicStream(const BasicStream & stream) = delete;

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
        DataSink* _dataSink;
    };

    template<class ConnectionType>
    class BasicServer : public Socket
    {
    public:
        typedef std::function<void(IStream* stream)> ConnectHandler;
        typedef std::function<void(IStream* stream)> DisconnectHandler;

        BasicServer() {}

        virtual int32_t startBindListen(const std::string& host, int32_t port, int32_t backlog)=0;
        virtual void OnConnect(ConnectHandler handler)=0;
        virtual void OnDisconnect(DisconnectHandler handler)=0;

        virtual ConnectionType acceptClientOfServer(int32_t listenfd)=0;
    };
}