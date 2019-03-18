#pragma once

#include "ByteArray.h"

#include <string>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>

namespace translayor
{
    class IStream;

    class BaseEvent
    {
    public:
        BaseEvent(){}
        BaseEvent(const std::string& type,const ByteArray& data,
                    IStream* stream) :
                    _type(type),_data(data),_stream(stream)
        {
        }

    private:
        std::string _type;
        ByteArray _data;
        IStream* _stream;
    };
}