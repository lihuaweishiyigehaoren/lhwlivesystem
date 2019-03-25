

#pragma once

#include "Severity.h"

#include <vector>
#include <map>
#include <set>

namespace hurricane {
namespace logging {

class IOStreamManager {
public:
    static IOStreamManager& GetInstance();

    ~IOStreamManager();

    std::vector<std::ostream*> GetDefaultOutputStreams(Severity severity);
    void SetOutputStream(std::ostream* outputStream, bool toManage = true);
    void SetOutputStream(hurricane::logging::Severity severity,
                         std::ostream* outputStream, bool toManage = true);
    void SetOutputStream(std::vector<hurricane::logging::Severity> severities,
                         std::ostream* outputStream, bool toManage = true);

    void SetOutputFile(const std::string& fileName);
    void SetOutputFile(hurricane::logging::Severity severity, const std::string& fileName);
    void SetOutputFile(std::vector<hurricane::logging::Severity> severities, const std::string& fileName);

private:
    IOStreamManager();
    std::ostream* CreateOutputFile(const std::string& fileName);

private:
    std::map<Severity, std::vector<std::ostream*>> _defaultOutputStreams;
    std::set<std::ostream*> _managedStreams;
};

}
}
