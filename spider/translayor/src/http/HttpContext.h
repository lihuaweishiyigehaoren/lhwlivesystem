#pragma once

#include "../ByteArray.h"
#include <map>
#include <cstring>
#include <vector>

typedef std::vector<std::string> StdStringList;

class HttpContext
{
public:
    virtual ~HttpContext(){}

    // 用于从_headers映射表中找出属性名对应的属性值
    const std::string& GetHeader(const std::string& name) const {
        return _headers.at(name);
    }

    // 设置HTTP头部属性
    void SetHeader(const std::string& name, const std::string& value) {
        _headers[name] = value;
    }

    // 用于检测头部中是否包含某个属性
    bool HasHeader(const std::string& name) const {
        return _headers.find(name) != _headers.end();
    }

    StdStringList GetHeaderNames() const;

    // 用于获取HTTP消息中的数据
    const std::string& GetContent() const {
        return _content;
    }

    void SetContent(const std::string& content);

    const std::string& GetVersion() const {
        return _version;
    }

    void SetVersion(const std::string& version) {
        _version = version;
    }

    // 负责解析字符串列表(每个字符串代表一行),生成Http消息对象
    virtual void ParseStdStringList(const StdStringList& stringList);
    virtual std::string ToStdString() const; // 将消息转换为字符串
 
    static HttpContext FromStdStringList(const StdStringList& stringList);// 根据字符串创建消息对象

private:
    std::string _version;
    std::map<std::string, std::string> _headers;
    std::string _content;
};

