#pragma once

#include "IoLoop.h"
#include "Net.h"

#include "EPollClient.h"
#include "LhwClientConnected.h"
#include "LhwServer.h"
#include "EPollStream.h"

namespace translayor 
{
    typedef LhwServer TcpServer;
    typedef LhwClientConnected TcpConnection;
    typedef EPollClient TcpClient;
    typedef EPollStream TcpStream;
}