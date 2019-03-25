

#pragma once

#include "Logger.h"

namespace hurricane {
namespace logging {

class ExpressionLogger : public Logger {
public:
    ExpressionLogger(Severity severity,
           const std::string& sourceFile, int32_t sourceLine, const std::string& expression);
    virtual ~ExpressionLogger();

    std::string GetExpression() const;
    void SetExpression(const std::string& expression);

private:
    std::string _expression;
};

}
}
