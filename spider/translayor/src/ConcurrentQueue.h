// 消息队列

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace translayor
{
    template<class Type>
    class ConcurrentQueue
    {
        ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;// 禁用赋值
        ConcurrentQueue(const ConcurrentQueue& other) = delete;// 禁用复制

    public:
        ConcurrentQueue() : 
        _queue(),_mutex(),_condition()
        {

        }
        virtual ~ConcurrentQueue(){}

        /*
        * 函数描述:将记录加入到队列中,使用互斥锁和条件量同步.当加入记录成功时通过notify_one来激活某个等待的线程
        */
        void Push(Type record)
        {
            std::lock_guard<std::mutex> lock(_mutex); //析构中自动执行unlock()
            _queue.push(record);
            _condition.notify_one();// 随机挑选并激活某个在条件量上等待的线程
        }

        /*
        * 函数描述:首先判断是否为阻塞模式,如果是,则循坏等待队列非空(有元素)为止.
        * 如果是非阻塞模式,检查一下队列中是否有元素,如果没有则返回false.如果有元素,则从队列中取出元素
        * 并使用std::move触发移动构造函数,将其赋值给用户传递的值,接着我们将元素从队列中删除,并返回true
        */
        bool Pop(Type &record,bool isBlocked = true)
        {
            if(isBlocked)
            {
                std::unique_lock<std::mutex> lock(_mutex); //更加灵活,功能更加强大,性能成本较高
                while(_queue.empty())
                {
                    _condition.wait(lock);// 线程在条件量上等待,并释放lock保护的互斥锁,直到另一个线程激活自身为止,如果被激活则会重新获取锁的所有权继续执行
                }
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
        mutable std::mutex _mutex; // 互斥锁
        std::condition_variable _condition; // 条件量
    };
}