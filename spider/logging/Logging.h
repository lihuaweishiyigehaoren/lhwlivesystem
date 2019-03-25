

#pragma once

#include "Interface.h"
#include "Logger.h"
#include "ExpressionLogger.h"
#include "CheckLogger.h"
#include "IOStreamManager.h"
#include "Check.h"
#include "System.h"

namespace hurricane {
namespace logging {

class LOGGING_API Logging {
public:
    static void SetLogFile(const std::string& fileName);
    static void SetLogFile(Severity severity, const std::string& fileName);
    static void SetLogFile(const std::vector<Severity> severities, const std::string& fileName);
};

}
}
