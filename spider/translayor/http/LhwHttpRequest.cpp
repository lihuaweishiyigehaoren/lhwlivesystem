
#include "LhwHttpRequest.h"
#include "String.h"
#include <iostream>

namespace  translayor {

    void LhwHttpRequest::parseStdString(const std::string& text) 
    {
        StdStringList stringList = splitString(text, '\n');

        for ( std::string& line: stringList ) 
        {
            line.pop_back();// 删除所有换行符,\n是在最后一位
        }

        parseStdStringList(stringList);
    }

    void LhwHttpRequest::parseStdStringList(const StdStringList& stringList) 
    {
        // std::string requestLine = stringList.front();
        // parseRequestLine(requestLine); // 处理第一行

        // StdStringList contextLines = stringList;
        // contextLines.erase(contextLines.begin());
        // LhwHttpContext::parseStdStringList(contextLines);
    }

    void LhwHttpRequest::parseRequestLine(const std::string& requestLine) 
    {
        StdStringList words = splitString(requestLine, ' ');

        // std::cout<<words<<std::endl;

        setMethod(words[0]);
        // setPath(words[1]);
        // setVersion(words[2]);// 第一个单词作为请求方法,第二个单词作为路径,第三个单词作为版本号
    }

    LhwHttpRequest LhwHttpRequest::fromStdString(const std::string& text) 
    {
        LhwHttpRequest request;
        request.parseStdString(text);

        return request;
    }

    LhwHttpRequest LhwHttpRequest::fromStdStringList(const StdStringList& stringList) 
    {
        LhwHttpRequest request;
        request.parseStdStringList(stringList);

        return request;
    }

}
