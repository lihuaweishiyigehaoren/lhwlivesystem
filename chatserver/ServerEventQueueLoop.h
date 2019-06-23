#pragma once
#include "LhwEventVector.h"
#include "LhwEventQueueLoop.h"

class ServerEventQueueLoop : public translayor::LhwEventQueueLoop
{
public:
    ServerEventQueueLoop(translayor::LhwEventVector * eventQueue) : LhwEventQueueLoop(eventQueue){}

protected:
    virtual void OnEvent(std::shared_ptr<translayor::BaseEvent> event) override
    {
        
    }
};