

#include "ExpressionLogger.h"

namespace logging {

ExpressionLogger::ExpressionLogger(Severity severity,
                                   const std::string& sourceFile, int32_t sourceLine,
                                   const std::string& expression)
        : Logger(severity, sourceFile,sourceLine),
          _expression(expression)
{
}

ExpressionLogger::~ExpressionLogger()
{
}

std::string ExpressionLogger::GetExpression() const
{
    return _expression;
}

void ExpressionLogger::SetExpression(const std::string& expression)
{
    _expression = expression;
}

}