

#include "BlockingQueue.h"
#include "LogItem.h"

#include <string>

namespace logging {

class LogItemQueue : public BlockingQueue<LogItem> {
public:
    static LogItemQueue& GetInstance();
    LogItemQueue(const LogItemQueue& queue) = delete;
    LogItemQueue& operator=(const LogItemQueue& queue) = delete;

private:
    LogItemQueue();
};


}
