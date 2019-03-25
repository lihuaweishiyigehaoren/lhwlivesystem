
#pragma once

#include "Severity.h"

#include <string>

namespace hurricane {
namespace logging {

class LoggerStream {
public:
    LoggerStream(Severity severity) : _severity(severity) {}
    virtual ~LoggerStream() {
    }

    Severity GetSeverity() const {
        return _severity;
    }

    void SetSeverity(Severity severity) {
        _severity = severity;
    }

    virtual void Output(const std::string& message) = 0;
    virtual void Submit() = 0;

private:
    Severity _severity;
};

}
}
