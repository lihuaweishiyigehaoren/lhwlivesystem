#include <iostream>

#include "LhwComponAlias.h"
#include "Logging.h"
#include "LhwEventVector.h"
#include "LhwIOLoopConfig.h"

#include "ServerEventQueueLoop.h"

const int32_t DefaultConnectPort = 8080;

int32_t main()
{
    translayor::LhwEventVector mainEventQuene(5);
    translayor::IoLoop::Get()->Start();

    translayor::PackageDataSink dataSink(&mainEventQuene);

    translayor::Server server;

    translayor::PackageDataSink* packageDataSink = &dataSink;
    server.startBindListen("127.0.0.1", DefaultConnectPort);

    // 通过server设置回调函数
    server.onConnect([=](translayor::IOStream* stream)
    {
        stream->onData(packageDataSink->StreamDataHandler(stream));
    }); 

    ServerEventQueueLoop serverQueue(&mainEventQuene);
    serverQueue.Start();

    return 0;
}
