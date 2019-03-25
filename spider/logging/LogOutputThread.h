
#pragma once

#include <thread>

namespace hurricane {
namespace logging {

class LogItemThread {
public:
    LogItemThread();
    ~LogItemThread();

private:
    void ThreadEntry();

private:
    bool _needToStop;
    std::thread _workThread;
};

}
}
