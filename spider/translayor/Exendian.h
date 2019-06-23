#ifndef NET_FRAMEWORK_EXENDIAN_H
#define NET_FRAMEWORK_EXENDIAN_H

#include <cstdint>
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
#include <Winsock2.h>
#else
#include <endian.h>
#endif

namespace meshy
{
    inline uint64_t ConvertHostToNetworkLongLong(uint64_t hostll)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
        return htonll(hostll);
#else
        return htobe64(hostll);
#endif
    }

    inline uint32_t ConvertHostToNetworkLong(uint32_t hostl)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
        return htonl(hostl);
#else
        return htobe32(hostl);
#endif
    }

    inline uint16_t ConvertHostToNetworkShort(uint16_t hosts)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
        return htons(hosts);
#else
        return htobe16(hosts);
#endif
    }

    inline uint64_t ConvertNetworkToHostLongLong(uint64_t networkll)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
        return ntohll(networkll);
#else
        return be64toh(networkll);
#endif
    }

    inline uint32_t ConvertNetworkToHostLong(uint32_t networkl)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
        return ntohl(networkl);
#else
        return be32toh(networkl);
#endif
    }

    inline uint16_t ConvertNetworkToHostShort(uint16_t networks)
    {
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
        return ntohs(networks);
#else
        return be16toh(networks);
#endif
    }
}

#endif //NET_FRAMEWORK_EXENDIAN_H
