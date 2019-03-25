

#include "CommonUtils.h"

#include <cstdio>

namespace translayor {
    int32_t SetNonBlocking(int32_t sockfd)
    {
        int32_t opts;

        opts = fcntl(sockfd, F_GETFL);
        if(opts < 0) {
            perror("fcntl(F_GETFL)\n");
            return -1;
        }
        opts = (opts | O_NONBLOCK);
        if(fcntl(sockfd, F_SETFL, opts) < 0) {
            perror("fcntl(F_SETFL)\n");
            return -1;
        }

        return 0;
    }
}
