#pragma once

#include "IoLoop.h"
#include "Net.h"

#include "EPollClient.h"
#include "EPollConnection.h"
#include "EPollServer.h"
#include "EPollStream.h"

namespace translayor 
{
    typedef EPollServer TcpServer;
    typedef EPollConnection TcpConnection;
    typedef EPollClient TcpClient;
    typedef EPollStream TcpStream;
}