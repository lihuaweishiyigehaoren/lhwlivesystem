#pragma once
#include <fcntl.h>
#include <cstdint>

namespace translayor {

    int32_t SetNonBlocking(int32_t sockfd);

}
