/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwThreadPool.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwThreadPool 自制的简易线程池
 * @desc:作用: 负责线程的调度
 */

#pragma once

#include "LhwThreadSafeQuene.h"

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
    class LhwThreadPool
    {
        // 删除赋值和复制构造函数
        LhwThreadPool& operator=(const LhwThreadPool&)=delete;
        LhwThreadPool(const LhwThreadPool& other)=delete;
    
    public:
        
       /*
        * 线程池初始化构造函数
        * @para threads 创建初始化线程的数量
        * @para handler 工作线程的处理函数
        */
        LhwThreadPool(int32_t threads,std::function<void(Type& record)> handler);
        virtual ~LhwThreadPool();

       /*
        * 用于提交一个记录,并由线程池中的工作线程进行处理
        * @para record 消息记录
        */
        void Submit(Type record);

    private:

        bool _shutdown;
        int32_t _threads;// 线程数量
        std::function<void(Type& record)> _handler; // 线程处理函数
        std::vector<std::thread> _workers; // 工作线程
        LhwThreadSafeQuene <Type> _tasks; // 消息队列
    };
    
    template<class Type>
    LhwThreadPool<Type>::LhwThreadPool(int32_t threads, std::function<void(Type &record)> handler)
            : _shutdown(false),
              _threads(threads),
              _handler(handler),
              _workers(),
              _tasks() {
        if (_threads < MIN_THREADS)
        {
            _threads = MIN_THREADS; // 默认是10条线程
        }
            
        for (int32_t i = 0; i < _threads; ++i)
            _workers.emplace_back(
                    [this] {
                        while (!_shutdown) 
                        {
                            Type record;
                            _tasks.pop(record, true);
                            _handler(record);
                        }
                    }
            );
    }

    template<class Type>
    LhwThreadPool<Type>::~LhwThreadPool() 
    {
        for (std::thread &worker: _workers)
            worker.join();
    }

    template<class Type>
    void LhwThreadPool<Type>::Submit(Type record) 
    {
        _tasks.push(record);
    }
}