

#include "LhwHttpResponse.h"
#include "String.h"

namespace translayor 
{
    std::string LhwHttpResponse::toStdString() const 
    {
        return getResponseLine() + LhwHttpContext::toStdString();
    }

    std::string LhwHttpResponse::getResponseLine() const 
    {
        return getVersion() + ' ' + itos(getStatusCode()) + ' ' + getStatusMessage() + "\r\n";
    }
}
