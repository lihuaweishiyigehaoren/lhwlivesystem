
#pragma once

#include "DataSink.h"
#include "LhwByteArray.h"
#include "LhwThreadPool.h"

namespace translayor 
{
    class LhwEventVector;

    class BaseEvent;

    class PackageDataSink : public DataSink 
    {
    public:
        PackageDataSink(LhwEventVector* eventQueue);

        ~PackageDataSink();

        int32_t Write(IOStream* stream, User buf, int64_t bytes) override;

    private:
        LhwEventVector * _eventQueue;
        LhwThreadPool<BaseEvent>* _threadPool;
        // LhwByteArray _data;
        int32_t _totalSize;
    };
}
