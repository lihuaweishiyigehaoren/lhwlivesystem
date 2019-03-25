
#pragma once

#include "Severity.h"
#include "LoggerStream.h"
#include "System.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

namespace hurricane {
namespace logging {

class Logger;

}
}

namespace std {

LOGGING_API hurricane::logging::Logger& endl(hurricane::logging::Logger& logger);

}

namespace hurricane {
namespace logging {

class LOGGING_API Logger {
public:
    Logger(Severity severity,
           const std::string& sourceFile, int32_t sourceLine);
    virtual ~Logger();

    template <class Value>
    Logger& Output(Value value) {
        if ( !_inOutput ) {
            _inOutput = true;
            OutputPrefix();
        }

        _bufferStream << value;

        return *this;
    }

    void endl();

    template <class Value>
    Logger& operator<<(Value value) {
        return Output(value);
    }

    Logger& operator<<(Logger& (*__pf)(Logger&))
    {
        return __pf(*this);
    }

    // The object returned by constructor can't use override operator<<.
    // So we use reference to return the reference of logger object.
    Logger& Reference() {
        return *this;
    }

    virtual void OutputPrefix();
    virtual std::string FormatPrefix();

private:
    Severity _severity;
protected:
    std::ostringstream _bufferStream;
    LoggerStream* _loggerStream;
private:
    std::string _sourceFile;
    std::string _sourceFileName;
    int32_t _sourceLine;
    bool _inOutput;
};

class LogMessageVoidify {
 public:
  LogMessageVoidify() { }
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(Logger&) { }
};

void WaitLoggerThread();

}
}
