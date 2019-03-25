
#include "HttpRequest.h"
#include "String.h"

namespace  translayor {
    void HttpRequest::ParseStdString(const std::string& text) {
        StdStringList stringList = SplitString(text, '\n');
        for ( std::string& line: stringList ) {
            line.pop_back();
        }

        ParseStdStringList(stringList);
    }

    void HttpRequest::ParseStdStringList(const StdStringList& stringList) {
        std::string requestLine = stringList.front();
        ParseRequestLine(requestLine);

        StdStringList contextLines = stringList;
        contextLines.erase(contextLines.begin());
        HttpContext::ParseStdStringList(contextLines);
    }

    void HttpRequest::ParseRequestLine(const std::string& requestLine) {
        StdStringList words = SplitString(requestLine, ' ');

        SetMethod(words[0]);
        SetPath(words[1]);
        SetVersion(words[2]);
    }

    HttpRequest HttpRequest::FromStdString(const std::string& text) {
        HttpRequest request;
        request.ParseStdString(text);

        return request;
    }

    HttpRequest HttpRequest::FromStdStringList(const StdStringList& stringList) {
        HttpRequest request;
        request.ParseStdStringList(stringList);

        return request;
    }

}
