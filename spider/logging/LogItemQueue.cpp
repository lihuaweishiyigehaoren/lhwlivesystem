
#include "LogItemQueue.h"

namespace logging {

LogItemQueue& LogItemQueue::GetInstance()
{
    static LogItemQueue queue;

    return queue;
}

LogItemQueue::LogItemQueue()
{
}

}
