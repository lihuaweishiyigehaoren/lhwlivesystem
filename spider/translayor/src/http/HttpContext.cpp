
#include "HttpContext.h"
#include "String.h"
#include <iostream>

StdStringList HttpContext::GetHeaderNames() const {
    StdStringList headerNames;

    for ( const auto& pair : _headers ) {
        headerNames.push_back(pair.first);
    }

    return headerNames;
}

HttpContext HttpContext::FromStdStringList(const StdStringList& stringList) {
    HttpContext context;
    context.ParseStdStringList(stringList);

    return context;
}

void HttpContext::ParseStdStringList(const StdStringList& stringList) {
    for ( const std::string& line : stringList ) {
        StdStringList words = SplitString(line, ':');

        if ( !words.size() ) {
            return;
        }

        std::string headerName = words[0];
        std::string headerValue = words[1];
        if ( words.size() > 2 ) {
            for ( int32_t wordIndex = 2; wordIndex < words.size(); ++ wordIndex ) {
                headerValue += ':';
                headerValue += words[wordIndex];
            }
        }

        headerValue.erase(headerValue.begin());

        SetHeader(headerName, headerValue);
    }
}

std::string HttpContext::ToStdString() const {
    std::string headersString;

    for ( const auto& headerPair : _headers ) {
        std::string headerString = headerPair.first + ':' + headerPair.second + "\r\n";
        headersString += headerString;
    }

    if ( _content.length() > 0 ) {
        headersString += "\r\n";
        headersString += _content;
    }

    return headersString;
}

void HttpContext::SetContent(const std::string& content) {
    _content = content;

    int32_t contentLength = static_cast<int32_t>(_content.size());
    if ( contentLength > 0 ) {
        SetHeader("Content-Length", itos(contentLength));
    }
}

