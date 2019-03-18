#pragma once

#include "ByteArray.h"

#include <functional>

namespace translayor
{
    class IStream {

    public:
        typedef std::function<int32_t(const char* buf,int64_t size)> DataHandler;
    
        virtual int32_t Receive(char* buffer,int32_t bufferSize,int32_t& readSize)=0;
        virtual int32_t Send(const ByteArray & byteArray)=0;
    
        virtual void OnData(DataHandler handler)=0;
        virtual DataHandler GetDataHandler()=0;
    
    };
}