
#pragma once

#include <thread>

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