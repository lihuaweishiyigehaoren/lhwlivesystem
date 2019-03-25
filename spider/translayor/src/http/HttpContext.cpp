
#include "HttpContext.h"
#include "String.h"
#include <iostream>

/*
*@desc: 返回HTTP消息头部中的所有属性名
*/
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

/*
*@desc: 解析字符串列表到HTTP
*/
void HttpContext::ParseStdStringList(const StdStringList& stringList) {
    for ( const std::string& line : stringList ) { // 这么写为了效率问题-遍历
        StdStringList words = SplitString(line, ':'); // 使用冒号分割字符串

        if ( !words.size() ) {
            return;
        }

        std::string headerName = words[0]; //以第一个单词作为属性名
        std::string headerValue = words[1]; 
        if ( words.size() > 2 ) {
            for ( int32_t wordIndex = 2; wordIndex < words.size(); ++ wordIndex ) {
                headerValue += ':';
                headerValue += words[wordIndex];
            }
        }

        headerValue.erase(headerValue.begin()); // 将后续的单词使用冒号连接起来作为属性值,并删除属性值的第一个空格

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

