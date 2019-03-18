#pragma once

#include "Loop.h"
#include <memory>

namespace translayor
{
    class EventQueue;

    class BaseEvent;

    class EventQueueLoop : public Loop
    {
    public:
        EventQueueLoop(EventQueue* queue);

    protected:
        virtual void _Run();
        
        /*
        *函数说明:用于指定触发某个事件时的回调函数
        */
        virtual void OnEvent(std::shared_ptr<BaseEvent> event)=0;

    private:
        EventQueue* _queue;
    };
}