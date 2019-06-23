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
 * @desc:作用:A等待一个事件,B触发事件,
 */

#pragma once

#include "LhwLoop.h"
#include "LhwEventVector.h"

#include <memory>

namespace translayor
{
    class LhwEventVector;

    class BaseEvent;

    class LhwEventQueueLoop : public LhwLoop
    {
    public:
        LhwEventQueueLoop(LhwEventVector * queue);

    protected:
        virtual void _run();
        
        /*
        * 用于指定触发某个事件时的回调函数
        */
        virtual void OnEvent(std::shared_ptr<BaseEvent> event)=0;

    private:
        LhwEventVector * _queue;
    };
}