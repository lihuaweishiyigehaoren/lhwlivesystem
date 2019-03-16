#pragma once

#include "ConcurrentQueue.h"

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#define MIN_THREADS 10

namespace translayor
{
    template<class Type>
    class ThreadPool
    {
        ThreadPool& operator=(const ThreadPool&)=delete;
        ThreadPool(const ThreadPool& other)=delete;
    
    public:
        /*
        *参数:一个是线程数量,一个是工作线程的处理函数
        *构造函数描述:根据用户指定的数字,创建特定数量的工作线程.然后循环创建所有的工作线程
        *每个工作线程的任务就是尝试从队列中获取数据,如果数据到来则执行用户指定的处理函数
        */
        ThreadPool(int32_t threads,std::function<void(Type& record)> handler);
        virtual ~ThreadPool();

        /*
        *函数描述: 用于提交一个记录,并由线程池中的工作线程进行处理
        */
        void Submit(Type record);

    private:
        bool _shutdown;
        int32_t _threads;
        std::function<void(Type& record) _handler;
        std::vector<std::thread> _workers;
        ConcurrentQueue <Type> _tasks;
    };
    
}
#include "thread_pool.tcc"