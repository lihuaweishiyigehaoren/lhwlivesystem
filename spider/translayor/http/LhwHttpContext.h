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
 * LhwHttpContext http上下文基类
 * @desc:作用: 保存了HTTP请求和响应中公用的部分,包括http版本号/头部信息/消息体
 */

#pragma once
#include "../LhwByteArray.h"
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> StdStringList;

class LhwHttpContext 
{
public:
    virtual ~LhwHttpContext() 
    {

    }

    const std::string& getHeader(const std::string& name) const 
    {
        return _headers.at(name);
    }

    void setHeader(const std::string& name, const std::string& value) 
    {
        _headers[name] = value;
    }

    bool hasHeader(const std::string& name) const 
    {
        return _headers.find(name) != _headers.end();
    }

    StdStringList getHeaderNames() const;

    const std::string& getContent() const 
    {
        return _content;
    }

    void setContent(const std::string& content);

    const std::string& getVersion() const 
    {
        return _version;
    }

    void setVersion(const std::string& version) 
    {
        _version = version;
    }

    /*
    * 解析字符串列表
    * @para stringList 字符串列表
    */
    virtual void parseStdStringList(const StdStringList& stringList);

    virtual std::string toStdString() const; // 将http转换为字符串

    /*
    * 根据字符串列表创建http消息对象
    * @para stringList 字符串列表
    */
    static LhwHttpContext fromStdStringList(const StdStringList& stringList);

private:
    std::string _version;
    std::map<std::string, std::string> _headers;
    std::string _content;
};
