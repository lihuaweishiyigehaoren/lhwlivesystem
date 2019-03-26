#pragma once
#include "EventQueue.h"
#include "EventQueueLoop.h"

class ServerEventQueueLoop : public translayor::EventQueueLoop
{
public:
    ServerEventQueueLoop(translayor::EventQueue* eventQueue) :
    EventQueueLoop(eventQueue){}
    // ~ServerEventQueueLoop();

protected:
    virtual void OnEvent(std::shared_ptr<translayor::BaseEvent> event) override
    {
        
    }
};