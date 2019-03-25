

#include "ThreadLoggerStream.h"
#include "LogItemQueue.h"

namespace hurricane {
namespace logging {

ThreadLoggerStream::ThreadLoggerStream(Severity severity) :
        LoggerStream(severity), _isSubmitted(false)
{
}

ThreadLoggerStream::~ThreadLoggerStream()
{
    Submit();
}

void ThreadLoggerStream::Output(const std::string& message)
{
    _buffer += message;
}

void ThreadLoggerStream::Submit()
{
    if ( !_isSubmitted ) {
        LogItem logItem(GetSeverity(), _buffer);
        LogItemQueue::GetInstance().Push(logItem);

        _isSubmitted = true;
    }
}

}
}
