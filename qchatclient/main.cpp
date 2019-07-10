#include "mainwindow.h"
#include <QApplication>
#include "LhwEventVector.h"
#include "LhwEventQueueLoop.h"
#include "LhwIOLoopConfig.h"
#include "PackageDataSink.h"
#include "LhwServer.h"
#include "LhwClient.h"
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
    SampleEventQueueLoop(translayor::LhwEventVector* eventQueue) :
            LhwEventQueueLoop(eventQueue) {}

protected:
    virtual void OnEvent(std::shared_ptr<translayor::BaseEvent> event) override
    {
        /*
       LOG(KLOG_DEBUG) << ("SampleEventQueueLoop::OnEvent");
        char buf[BUFSIZ]; // BUFSIZ is 1024
        sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);

        event->GetConnection()->Send(ByteArray(buf, strlen(buf)));
        LOG(KLOG_DEBUG) << ("SampleEventQueueLoop::OnEvent end");
         */
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    translayor::LhwEventVector mainEventQueue(5);
//    translayor::IoLoop::Get()->Start();

//    translayor::PackageDataSink dataSink(&mainEventQueue);

//    translayor::EPollClientPtr client =
//            translayor::LhwClient::connect("120.78.146.208", DefaultPort, &dataSink);

//    client->sendData(translayor::LhwByteArray("hello", 5));

    MainWindow w;
    w.show();

//    SampleEventQueueLoop sampleQueue(&mainEventQueue);
//    sampleQueue.Start();

    return a.exec();
}
