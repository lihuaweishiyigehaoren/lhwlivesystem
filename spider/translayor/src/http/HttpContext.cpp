#include "HttpContext.h"
#include "String.h"
#include <iostream>

StdStringList HttpContext::GetHeaderNames() const
{
    StdStringList headerNames;

    for( const auto& pair : _headers )
    {
        headerNames.push_back(pair.first);
    }

    return headerNames;
}