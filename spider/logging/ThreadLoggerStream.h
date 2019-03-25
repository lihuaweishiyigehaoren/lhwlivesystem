

#pragma once

#include "LoggerStream.h"

#include <string>
#include <iostream>
#include <vector>

namespace hurricane {
namespace logging {

class ThreadLoggerStream : public LoggerStream {
public:
    ThreadLoggerStream(Severity severity);
    virtual ~ThreadLoggerStream();

    virtual void Output(const std::string& message) override;
    virtual void Submit();

private:
    std::string _buffer;
    bool _isSubmitted;
};

}
}
