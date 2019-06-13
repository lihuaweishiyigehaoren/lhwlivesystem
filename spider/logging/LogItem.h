

#include "Logger.h"

#include <string>

namespace logging {

class LogItem {
public:
    LogItem() : _empty(true) {}

    LogItem(Severity severity, const std::string& content)
            : _empty(false), _severity(severity), _content(content) {
    }

    bool Empty() const {
        return _empty;
    }

    void SetEmpty(bool empty) {
        _empty = empty;
    }

    Severity GetSeverity() const {
        return _severity;
    }

    void SetSeverity(Severity severity) {
        _severity = severity;
    }

    const std::string& GetContent() const {
        return _content;
    }

    void SetContent(const std::string& content) {
        _content = content;
    }

private:
    bool _empty;
    Severity _severity;
    std::string _content;
};

}
