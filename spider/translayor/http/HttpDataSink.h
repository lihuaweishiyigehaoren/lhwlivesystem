
#pragma once
#include "LhwHttpRequest.h"
#include "../LhwComponAlias.h"

namespace translayor 
{
    class HttpDataSink 
    {
        public:
            virtual int OnDataIndication(Stream* stream, const LhwHttpRequest& request) = 0;
    };
}