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
            LOG(LOG_DEBUG) << "Thread onEvent sink!";

            std::string requestText = event.GetData().ToStdString();

            LhwHttpRequest request;
            request.parseStdString(requestText);

            LhwHttpResponse response;
            response.setVersion("HTTP/1.1");
            response.setStatusCode(200);
            response.setStatusMessage("OK");
            response.setContent("Hello! Sink in Thread!");

            event.GetStream()->sendData(LhwByteArray(response.toStdString())); // Send to peer

            LOG(LOG_DEBUG) << "Thread onEvent sink end.";
        });
    }

    PackageDataSink::~PackageDataSink() 
    {
        if (_threadPool) {
            delete _threadPool;
            _threadPool = nullptr;
        }
    }

    int32_t PackageDataSink::Write(IOStream* stream, const char* buf, int64_t bytes) 
    {
        _data.Concat(LhwByteArray(buf, static_cast<int32_t>(bytes)));
        // 保证是一个完整的包
        if (_data.size() >= _totalSize) {
            //_eventQueue->PostEvent(new BaseEvent("data", _data, connection));
            _threadPool->Submit(BaseEvent("data", _data, stream));

            _data.clear();
            _totalSize = 0;
        }

        return static_cast<int32_t>(bytes);
    }
}
