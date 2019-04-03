
#include "HttpRequest.h"
#include "String.h"
#include <iostream>

namespace  translayor {

    /*
    *@desc: 负责解析字符串,初始化HttpResquest
    **/
    void HttpRequest::ParseStdString(const std::string& text) {
        StdStringList stringList = SplitString(text, '\n');
        for ( std::string& line: stringList ) {
            line.pop_back();// 删除所有换行符
        }

        ParseStdStringList(stringList);
    }

    void HttpRequest::ParseStdStringList(const StdStringList& stringList) {
        std::string requestLine = stringList.front();
        ParseRequestLine(requestLine); // 处理第一行

        StdStringList contextLines = stringList;
        contextLines.erase(contextLines.begin());
        HttpContext::ParseStdStringList(contextLines);
    }

    void HttpRequest::ParseRequestLine(const std::string& requestLine) {
        StdStringList words = SplitString(requestLine, ' ');

        // std::cout<<words<<std::endl;

        SetMethod(words[0]);
        //SetPath(words[1]);
        //SetVersion(words[2]);// 第一个单词作为请求方法,第二个单词作为路径,第三个单词作为版本号
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
