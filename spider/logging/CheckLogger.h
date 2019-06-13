#pragma once

#include "ExpressionLogger.h"

namespace logging {

class CheckLogger : public ExpressionLogger {
public:
    CheckLogger(Severity severity,
           const std::string& sourceFile, int32_t sourceLine, const std::string& expression);
    virtual ~CheckLogger();

    virtual void OutputPrefix();
};

}
