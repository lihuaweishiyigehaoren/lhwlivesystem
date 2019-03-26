
#pragma once

namespace logging {

enum class Severity {
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

}

const logging::Severity LOG_DEBUG = logging::Severity::Debug;
const logging::Severity LOG_INFO = logging::Severity::Info;
const logging::Severity LOG_WARNING = logging::Severity::Warning;
const logging::Severity LOG_ERROR = logging::Severity::Error;
const logging::Severity LOG_FATAL = logging::Severity::Fatal;
