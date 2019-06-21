#include "Net.h"
#include "EventQueue.h"
#include "LhwEventQueueLoop.h"
#include "IoLoop.h"
#include "PackageDataSink.h"
#include "LhwServer.h"
#include "EPollClient.h"
#include "Logging.h"

#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <memory>

using namespace std;

const int32_t DefaultPort = 8080;
class SampleEventQueueLoop : public translayor::LhwEventQueueLoop {
public:
    SampleEventQueueLoop(translayor::EventQueue* eventQueue) :
            LhwEventQueueLoop(eventQueue) {}

protected:
    virtual void OnEvent(std::shared_ptr<translayor::BaseEvent> event) override {
        /*
       LOG(KLOG_DEBUG) << ("SampleEventQueueLoop::OnEvent");
        char buf[BUFSIZ]; // BUFSIZ is 1024
        sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);

        event->GetConnection()->Send(ByteArray(buf, strlen(buf)));
        LOG(KLOG_DEBUG) << ("SampleEventQueueLoop::OnEvent end");
         */
    }
};

// using hurricane::logging::Logging;

int32_t main() {
    logging::Logging::SetLogFile("client-all.log");
    logging::Logging::SetLogFile({ LOG_INFO, LOG_DEBUG }, "client-output.log");
    logging::Logging::SetLogFile({ LOG_WARNING, LOG_ERROR, LOG_FATAL }, "client-error.log");

    translayor::EventQueue mainEventQueue(5);
    translayor::IoLoop::Get()->Start();

    translayor::PackageDataSink dataSink(&mainEventQueue);

    // translayor::EPollClientPtr client = translayor::EPollClient::Connect("120.78.146.208", DefaultPort, &dataSink);
    translayor::EPollClientPtr client = translayor::EPollClient::Connect("127.0.0.1", DefaultPort, &dataSink);

    client->Send(translayor::ByteArray("hello", 5));

    SampleEventQueueLoop sampleQueue(&mainEventQueue);
    sampleQueue.Start();

    return 0;
}