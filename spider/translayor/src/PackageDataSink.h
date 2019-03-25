
#pragma once

#include "DataSink.h"
#include "ByteArray.h"
#include "ThreadPool.h"

namespace translayor 
{
    class EventQueue;

    class BaseEvent;

    class PackageDataSink : public DataSink 
    {
    public:
        PackageDataSink(EventQueue* eventQueue);

        ~PackageDataSink();

        int32_t Write(IStream* stream, const char* buf, int64_t bytes) override;

    private:
        EventQueue* _eventQueue;
        ThreadPool<BaseEvent>* _threadPool;
        ByteArray _data;
        int32_t _totalSize;
    };
}
