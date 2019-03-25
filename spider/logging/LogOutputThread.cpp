
#include "LogOutputThread.h"
#include "LogItemQueue.h"
#include "IOStreamManager.h"

namespace hurricane {
namespace logging {

static LogItemThread LogItemThreadInstance;

LogItemThread::LogItemThread() : _needToStop(false)
{
    _workThread = std::thread(&LogItemThread::ThreadEntry, this);
    _workThread.detach();
}

LogItemThread::~LogItemThread()
{
    _needToStop = true;
}

void LogItemThread::ThreadEntry()
{
    LogItemQueue& logItemQueue = LogItemQueue::GetInstance();

    while ( !_needToStop ) {
        LogItem logItem;
        logItemQueue.Pop(logItem);

        std::vector<std::ostream*> outputStreams =
                hurricane::logging::IOStreamManager::GetInstance().GetDefaultOutputStreams(
                    logItem.GetSeverity());
        for ( std::ostream* outputStream : outputStreams ) {
            *outputStream << logItem.GetContent();
        }
    }
}

}
}
