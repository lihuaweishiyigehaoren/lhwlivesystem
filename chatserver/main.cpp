#include <iostream>

#include "LhwComponAlias.h"
#include "Logging.h"
#include "LhwEventVector.h"
#include "LhwIOLoopConfig.h"

#include "ServerEventQueueLoop.h"

const int32_t DefaultConnectPort = 8080;

int32_t main()
{
    logging::Logging::SetLogFile("all.log");
    logging::Logging::SetLogFile({ LOG_INFO, LOG_DEBUG}, "out.log");
    logging::Logging::SetLogFile({ LOG_WARNING, LOG_ERROR, LOG_FATAL}, "error.log");

    translayor::LhwEventVector mainEventQuene(5);
    translayor::IoLoop::Get()->Start();

    translayor::PackageDataSink dataSink(&mainEventQuene);

    translayor::Server server;

    translayor::PackageDataSink* packageDataSink = &dataSink;
    server.startBindListen("127.0.0.1", DefaultConnectPort);
    server.onConnect([=](translayor::IOStream* stream)
    {
        stream->onData(packageDataSink->StreamDataHandler(stream));
    });

    ServerEventQueueLoop serverQueue(&mainEventQuene);
    serverQueue.Start();

    return 0;
}
