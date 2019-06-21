#pragma once
#include "EventQueue.h"
#include "LhwEventQueueLoop.h"

class ServerEventQueueLoop : public translayor::LhwEventQueueLoop
{
public:
    ServerEventQueueLoop(translayor::EventQueue* eventQueue) : LhwEventQueueLoop(eventQueue){}

protected:
    virtual void OnEvent(std::shared_ptr<translayor::BaseEvent> event) override
    {
        
    }
};