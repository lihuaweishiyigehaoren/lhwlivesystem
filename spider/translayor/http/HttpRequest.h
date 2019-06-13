#pragma once
#include "HttpContext.h"

namespace translayor {
    // 在HttpContext的基础上实现,描述HTTP的请求信息,在HttpContext的基础上需要增加诸如方法类型和路径之类的信息
    class HttpRequest : public HttpContext {
    public:
        HttpRequest() {}
        void ParseStdString(const std::string& text);
        virtual void ParseStdStringList(const StdStringList& stringList) override;

        static HttpRequest FromStdString(const std::string& text);
        static HttpRequest FromStdStringList(const StdStringList& stringList);

        const std::string& GetMethod() const {
            return _method;
        }

        const std::string& GetPath() const {
            return _path;
        }

        void SetMethod(const std::string& method) {
            _method = method;
        }

        void SetPath(const std::string& path) {
            _path = path;
        }

    private:
        void ParseRequestLine(const std::string& requestLine);

    private:
        std::string _method;
        std::string _path;
    };
}
