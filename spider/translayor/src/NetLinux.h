#pragma once

#include <cstdint>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>

namespace translayor
{
    typedef int32_t NativeSocket;
    typedef ::sockaddr_in NativeSocketAddress;
    typedef ::epoll_event NativeSocketEvent;
}