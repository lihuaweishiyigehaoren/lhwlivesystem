/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEpollLoop.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

#include "LhwEventQueueLoop.h"

namespace translayor
{
    LhwEventQueueLoop::LhwEventQueueLoop(LhwEventVector * queue) : 
    _queue(queue)
    {

    }

    void LhwEventQueueLoop::_run()
    {
        while(true)
        {
            std::shared_ptr<BaseEvent> event = _queue->GetEvent();
            if(!event)
            {
                continue;
            }

            OnEvent(event);
        }
        
    }
}