

#include "HttpResponse.h"
#include "String.h"

namespace translayor {
    std::string HttpResponse::ToStdString() const {
        return GetResponseLine() +
               HttpContext::ToStdString();
    }

    std::string HttpResponse::GetResponseLine() const {
        return GetVersion() + ' ' + itos(GetStatusCode()) + ' ' + GetStatusMessage() + "\r\n";
    }
}
