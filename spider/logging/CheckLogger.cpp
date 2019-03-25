#include "CheckLogger.h"

#include <cassert>

namespace hurricane {
namespace logging {

CheckLogger::CheckLogger(Severity severity,
                         const std::string& sourceFile, int32_t sourceLine,
                         const std::string& expression) :
        ExpressionLogger(severity, sourceFile, sourceLine, expression)
{

}

CheckLogger::~CheckLogger()
{
    Output("\n");
    _loggerStream->Output(_bufferStream.str());
    _loggerStream->Submit();
    WaitLoggerThread();
#ifdef WIN32
#undef NDEBUG
    assert(0);
#else
    exit(EXIT_FAILURE);
#endif
}

void CheckLogger::OutputPrefix()
{
    Logger::OutputPrefix();
    Output(std::string("Expression '") + GetExpression() + "' failed. ");
}

}
}
