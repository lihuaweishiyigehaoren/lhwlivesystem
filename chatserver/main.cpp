#include <iostream>

#include "TransLayor.h"
#include "Logging.h"
#include "EventQueue.h"
#include "IoLoop.h"

#include "ServerEventQueueLoop.h"

const int32_t DefaultConnectPort = 8080;

int32_t main()
{
    logging::Logging::SetLogFile("all.log");
    logging::Logging::SetLogFile({ LOG_INFO, LOG_DEBUG}, "out.log");
    logging::Logging::SetLogFile({ LOG_WARNING, LOG_ERROR, LOG_FATAL}, "error.log");

    translayor::EventQueue mainEventQuene(5);
    translayor::IoLoop::Get()->Start();

    translayor::PackageDataSink dataSink(&mainEventQuene);

    translayor::TcpServer server;

    translayor::PackageDataSink* packageDataSink = &dataSink;
    server.Listen("127.0.0.1", DefaultConnectPort);
    server.OnConnect([=](translayor::IStream* stream)
    {
        stream->OnData(packageDataSink->StreamDataHandler(stream));
    });

    ServerEventQueueLoop serverQueue(&mainEventQuene);
    serverQueue.Start();

    return 0;
}
