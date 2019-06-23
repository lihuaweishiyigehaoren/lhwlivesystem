
#pragma once

#include "LhwLinuxEpoll.h"

#include "LhwEpollStream.h"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

namespace translayor 
{
    class EPollLoop;

    class LhwClientConnected : public LhwEpollStream 
    {
    public:
        LhwClientConnected(NativeSocket nativeSocket) :
                LhwEpollStream(nativeSocket) { }
                
        virtual ~LhwClientConnected() { }

        LhwClientConnected(const LhwClientConnected& connection) = delete;
    };

    typedef std::shared_ptr <LhwClientConnected> Collectioner;

}