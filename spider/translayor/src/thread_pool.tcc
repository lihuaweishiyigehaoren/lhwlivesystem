
#pragma once

namespace translayor
{
    template<class Type>
    ThreadPool<Type>::ThreadPool(int32_t threads,std::function<void(Type &record)> handler) :
    _shutdown(false),
    _threads(threads),
    _workers(),
    _tasks()
    {
        if(_threads < MIN_THREADS)
        {
            _threads = MIN_THREADS;
        }
        
        for(int32_t i = 0;i<_threads;++i)
        {
            _workers.emplace_back(
                [this] {
                    while(!_shutdown){
                        Type record;
                        _tasks.Pop(record,true);
                        _handler(record);
                    }
                    
                }
            );
        }
    }

    // 析构函数中会遍历所有线程并逐一等待,直到所有线程结束为止
    template<class Type>
    ThreadPool<Type>::~ThreadPool()
    {
        for(std::thread &worker: _workers)
        {
            worker.join();
        }
    }

    // 直接将一个记录对象放入任务队列即可
    template<class Type>
    void ThreadPool<Type>::Submit(Type record)
    {
        _tasks.Push(record);
    }
}