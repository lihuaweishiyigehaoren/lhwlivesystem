/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEventVector.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwEventVector 放置事件的容器-事件队列
 * @desc:作用: 
 */


#pragma once

#include "LhwByteArray.h"

#include <string>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>

namespace translayor
{
    class IOStream;

    class BaseEvent
    {
    public:
        BaseEvent(){}
        BaseEvent(const std::string& type,const LhwByteArray& data,IOStream* stream) :
                    _type(type),
                    _data(data),
                    _stream(stream)
        {

        }

        void SetData(const LhwByteArray& data)
        {
            _data = data;
        }

        const LhwByteArray& GetData() const
        {
            return _data;
        }

        void SetType(const std::string& type)
        {
            _type = type;
        }

        const std::string& GetType() const
        {
            return _type;
        }

        void SetStream(IOStream* stream)
        {
            _stream = stream;
        }

        IOStream* GetStream() const
        {
            return _stream;
        }

    private:
        std::string _type; // 事件类型
        LhwByteArray _data; // 事件数据
        IOStream * _stream; // 事件对应的数据流
    };

    class LhwEventVector
    {
    public:
        LhwEventVector(int32_t timeout=0) :
        _timeout(timeout){

        }

        ~LhwEventVector(){}

        /*
        * 将事件加入到容器中
        * @para event 事件
        */
        void PostEvent(BaseEvent * event)
        {
            std::unique_lock<std::mutex> locker(_mutex);
            _events.push_back(std::shared_ptr<BaseEvent>(event));
        }

        /*
        * 从容器中获取事件
        */
        std::shared_ptr<BaseEvent> GetEvent()
        {
            std::unique_lock<std::mutex> locker(_mutex);

            if(_events.empty())
            {
                if(_timeout==0)
                {
                    return nullptr;
                }

                _waitCondition.wait_for(locker,std::chrono::milliseconds(_timeout));
            }

            if(!_events.empty())
            {
                std::shared_ptr<BaseEvent> event = _events.front();
                _events.erase(_events.begin());

                return event;
            }

            return nullptr;
        }

    private:
    
        std::vector<std::shared_ptr<BaseEvent>> _events;  // 事件容器
        std::mutex _mutex;
        std::condition_variable _waitCondition;

        int32_t _timeout; // 超时时间

    };
}