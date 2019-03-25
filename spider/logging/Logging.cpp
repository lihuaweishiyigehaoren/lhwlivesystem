

#include "Logging.h"
#include "IOStreamManager.h"

namespace hurricane {
namespace logging {

void Logging::SetLogFile(const std::string& fileName)
{
    IOStreamManager::GetInstance().SetOutputFile(fileName);
}

void Logging::SetLogFile(Severity severity, const std::string& fileName)
{
    IOStreamManager::GetInstance().SetOutputFile(severity, fileName);
}

void Logging::SetLogFile(const std::vector<Severity> severities, const std::string& fileName)
{
    IOStreamManager::GetInstance().SetOutputFile(severities, fileName);
}

}
}
