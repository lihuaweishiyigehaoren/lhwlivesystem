#pragma once
#include <fcntl.h>
#include <cstdint>

#define MAX_EVENT_COUNT 32000
#define MAX_RECV_BUFF 65535

namespace translayor 
{
    int32_t SetNonBlocking(int32_t sockfd);
}
