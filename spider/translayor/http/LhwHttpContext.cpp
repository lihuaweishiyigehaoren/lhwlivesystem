
#include "LhwHttpContext.h"
#include "String.h"
#include <iostream>

/*
*@desc: 返回HTTP消息头部中的所有属性名
*/
StdStringList LhwHttpContext::getHeaderNames() const 
{
    StdStringList headerNames;

    for ( const auto& pair : _headers ) 
    {
        headerNames.push_back(pair.first);
    }

    return headerNames;
}

LhwHttpContext LhwHttpContext::fromStdStringList(const StdStringList& stringList) 
{
    LhwHttpContext context;
    context.parseStdStringList(stringList);

    return context;
}

void LhwHttpContext::parseStdStringList(const StdStringList& stringList) 
{
    // 每个字符串代表一行
    for ( const std::string& line : stringList ) { // 这么写为了效率问题-遍历
        StdStringList words = splitString(line, ':'); // 使用冒号分割字符串

        if ( !words.size() ) 
        {
            return;
        }

        std::string headerName = words[0]; //以第一个单词作为属性名
        std::string headerValue = words[1]; 
        if ( words.size() > 2 ) 
        {
            for ( int32_t wordIndex = 2; wordIndex < words.size(); ++ wordIndex ) {
                headerValue += ':';
                headerValue += words[wordIndex];
            }
        }

        // 将后续的单词使用冒号连接起来作为属性值,并删除属性值的第一个空格
        headerValue.erase(headerValue.begin()); 

        setHeader(headerName, headerValue);
    }
}

std::string LhwHttpContext::toStdString() const 
{
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

void LhwHttpContext::setContent(const std::string& content) 
{
    _content = content;

    int32_t contentLength = static_cast<int32_t>(_content.size());
    if ( contentLength > 0 ) 
    {
        setHeader("Content-Length", itos(contentLength));
    }
}

