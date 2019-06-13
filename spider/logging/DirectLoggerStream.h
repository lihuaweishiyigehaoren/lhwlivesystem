

#pragma once

#include "LoggerStream.h"

#include <ostream>
#include <vector>

namespace logging {

class DirectLoggerStream : public LoggerStream {
public:
    DirectLoggerStream(Severity severity);
    virtual ~DirectLoggerStream();

    virtual void Output(const std::string& message) override;
    virtual void Submit() override;

private:
    std::vector<std::ostream*> _outputStreams;
};

}