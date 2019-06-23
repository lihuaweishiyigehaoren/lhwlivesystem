/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwThreadSafeQuene.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwThreadSafeQuene 实现线程安全的消息队列
 * @desc:作用: 消息队列对于生产者-消费者模型异常重要,事件触发者只需要向消息队列放入消息即可
 */


#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace translayor
{
    template<class Type>
    class LhwThreadSafeQuene
    {

        LhwThreadSafeQuene& operator=(const LhwThreadSafeQuene&) = delete;// 禁用赋值

        LhwThreadSafeQuene(const LhwThreadSafeQuene& other) = delete;// 禁用复制

    public:
        LhwThreadSafeQuene() : 
        // 调用其默认构造函数
        _queue(),
        _mutex(),
        _condition()
        {

        }

        virtual ~LhwThreadSafeQuene()
        {

        }

       /*
        * 添加消息到队列中
        * @para record Type类型的消息
        */
        void push(Type record)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push(record);
            _condition.notify_one();// 随机挑选并激活某个在条件量上等待的线程
        }

       /*
        * 添加消息到队列中
        * @para record Type类型的消息
        * @para isBlocked 判断是否阻塞
        */
        bool pop(Type &record,bool isBlocked = true)
        {
            if(isBlocked)
            {
                // 参考自C并发编程 unique_lock 更加灵活,但是成本比lock_grand高
                std::unique_lock<std::mutex> lock(_mutex); 
                // while(_queue.empty())
                // {
                //     // wait()函数将解锁互斥量,并且将这个线程置于阻塞或等待状态
                //     _condition.wait(lock); 
                // }
                _condition.wait(lock,[this]{return !_queue.empty();}); // wait的时候锁是释放的,条件达成,获得锁,否则阻塞
            }
            else
            {
                std::lock_guard<std::mutex> lock(_mutex);
                if(_queue.empty())
                {
                    return false;
                }
            }

            record = std::move(_queue.front());
            _queue.pop();
            return true;
        }

        int32_t Size()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            return _queue.size();
        }

        bool Empty()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            return _queue.empty();
        }

    private:
        std::queue <Type> _queue; // 队列
        // std::mutex 在上锁的时候会改变内部的结构,加上mutable是为了说明mutex改变可以认为对象为改变
        mutable std::mutex _mutex; // 使用mutable上锁的原因: 为了在const成员函数中上锁
        std::condition_variable _condition; // 条件量
    };
}