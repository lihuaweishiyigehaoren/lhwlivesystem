
#include "LogItemQueue.h"

namespace hurricane {
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
}
