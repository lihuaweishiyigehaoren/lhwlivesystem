
#pragma once

namespace hurricane {
namespace logging {

enum class Severity {
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

}
}

const hurricane::logging::Severity LOG_DEBUG = hurricane::logging::Severity::Debug;
const hurricane::logging::Severity LOG_INFO = hurricane::logging::Severity::Info;
const hurricane::logging::Severity LOG_WARNING = hurricane::logging::Severity::Warning;
const hurricane::logging::Severity LOG_ERROR = hurricane::logging::Severity::Error;
const hurricane::logging::Severity LOG_FATAL = hurricane::logging::Severity::Fatal;
