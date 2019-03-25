
#pragma once
#include "Net.h"
#include "HttpRequest.h"

namespace translayor 
{
class HttpDataSink {
    virtual OnDataIndication(TcpStream* stream, const HttpRequest& request) = 0;
};
}