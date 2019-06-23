#pragma once

#include "LhwIOLoopConfig.h"

#include "LhwClient.h"
#include "LhwClientConnected.h"
#include "LhwServer.h"
#include "LhwEpollStream.h"

namespace translayor 
{
    typedef LhwServer Server;
    typedef LhwClientConnected Connection;
    typedef LhwClient Client;
    typedef LhwEpollStream Stream;
}