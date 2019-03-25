#pragma once

#include "HttpContext.h"

namespace translayor {
    class HttpResponse : public HttpContext {
    public:
        HttpResponse() {}
        virtual std::string ToStdString() const override;

        int32_t GetStatusCode() const {
            return _statusCode;
        }

        void SetStatusCode(int32_t statusCode) {
            _statusCode = statusCode;
        }

        const std::string& GetStatusMessage() const {
            return _statusMessage;
        }

        void SetStatusMessage(const std::string& message) {
            _statusMessage = message;
        }

    private:
        std::string GetResponseLine() const;

        int32_t _statusCode;
        std::string _statusMessage;
    };
}