#include "PackageDataSink.h"
#include "LhwEventVector.h"
#include "Logging.h"
#include "http/LhwHttpContext.h"
#include "http/LhwHttpRequest.h"
#include "http/LhwHttpResponse.h"

namespace translayor 
{
    PackageDataSink::PackageDataSink(LhwEventVector* eventQueue) : 
    _eventQueue(eventQueue), _totalSize(0) {
        _threadPool = new LhwThreadPool<BaseEvent>(10, [&](BaseEvent& event) 
        {
            LOG(LOG_DEBUG) << "into thread";

            // std::string requestText = event.GetData().ToStdString();
            User requestText = event.GetData();
            
            LOG(LOG_DEBUG) << requestText.username; // 打印发送请求的用户名

            // LhwHttpRequest request;
            // request.parseStdString(requestText);

            // 根据不同的请求类型,发送相应的回复

            LhwHttpResponse response;
            response.setVersion("HTTP/1.1");
            response.setStatusCode(200);
            response.setStatusMessage("OK");
            response.setContent("I have got your message");

            // LhwByteArray reply(response.toStdString());
            event.GetStream()->dataProcess(requestText);
            event.GetStream()->postDataToBuffer(requestText); // Send to peer

            LOG(LOG_DEBUG) << "get data"; 
        });
    }

    PackageDataSink::~PackageDataSink() 
    {
        if (_threadPool) 
        {
            delete _threadPool;
            _threadPool = nullptr;
        }
    }

    int32_t PackageDataSink::Write(IOStream* stream, User buf, int64_t bytes) 
    {
        LOG(LOG_DEBUG) << "Write";
        // _data.Concat(LhwByteArray(buf, static_cast<int32_t>(bytes)));
        // 保证是一个完整的包
        if (static_cast<int32_t>(bytes) >= _totalSize) 
        {
            // _eventQueue->PostEvent(new BaseEvent("data", _data, stream));
            _threadPool->Submit(BaseEvent("data", buf, stream));

            // _data.clear();
            _totalSize = 0;
        }

        return static_cast<int32_t>(bytes);
    }
}
