
#pragma once

#include "NetLinux.h"
#include "Net.h"

#include "EPollStream.h"

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

    class LhwClientConnected : public EPollStream {
    public:
        LhwClientConnected(NativeSocket nativeSocket) :
                EPollStream(nativeSocket) { }
        virtual ~LhwClientConnected() { }

        LhwClientConnected(const LhwClientConnected& connection) = delete;
    };

    typedef std::shared_ptr <LhwClientConnected> Collectioner;

}