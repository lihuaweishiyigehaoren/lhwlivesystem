/**
* @version 1.0.0
* @author lihuawei
* @mail lihuawei@hust.edu.cn
* @see https://github.com/lihuaweishiyigehaoren/lhwlivesystem
* @file LhwEpollLoop.h
* lhwlivesystem第一版本发布
* 版本号1.0.0
*/

/*
 * LhwHttpRequest HTTP 请求类
 * @desc:作用: 在LhwHttpContext基础上增加了一些方法
 */

#pragma once

#include "LhwHttpContext.h"

namespace translayor {
    
    class LhwHttpRequest : public LhwHttpContext 
    {
    public:
        LhwHttpRequest() {}

        /*
        * 解析字符串列表,初始化Lhwrequest对象
        * @para text 字符串列表
        */
        void parseStdString(const std::string& text);

        /*
        * 解析字符串列表,初始化request对象
        * @para stringList 字符串列表
        */
        virtual void parseStdStringList(const StdStringList& stringList) override;

        static LhwHttpRequest fromStdString(const std::string& text);
        static LhwHttpRequest fromStdStringList(const StdStringList& stringList);

        const std::string& getMethod() const 
        {
            return _method;
        }

        const std::string& getPath() const 
        {
            return _path;
        }

        void setMethod(const std::string& method) 
        {
            _method = method;
        }

        void setPath(const std::string& path) 
        {
            _path = path;
        }

    private:
        void parseRequestLine(const std::string& requestLine);

    private:
        std::string _method; // Get Post等请求
        std::string _path;
        /*
        * 结构
        * 请求行: GET /index.html HTTP/1.1
        * 消息头: User Agent: Mozilla/5.0
        *        Accept: image/gif, image/jpeg
        *        .......
        * 消息体: 消息体仅在post方式请求时候插入
        */
    };
}
