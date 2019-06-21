/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEpollLoop.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwEpollLoop 事件循环
 * @desc:作用:epoll的事件循环类,负责不断的监听来自epoll的事件,并对事件进行处理
 */

#pragma once

#include "LhwLoop.h"
#include <memory>

namespace translayor
{
    class EventQueue;

    class BaseEvent;

    class LhwEventQueueLoop : public LhwLoop
    {
    public:
        LhwEventQueueLoop(EventQueue* queue);

    protected:
        virtual void _run();
        
        /*
        *函数说明:用于指定触发某个事件时的回调函数
        */
        virtual void OnEvent(std::shared_ptr<BaseEvent> event)=0;

    private:
        EventQueue* _queue;
    };
}