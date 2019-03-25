#pragma once
#include "HttpContext.h"

namespace translayor {
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
