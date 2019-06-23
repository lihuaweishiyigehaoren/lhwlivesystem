#pragma once

#include "PackageDataSink.h"
#include "LhwClientConnected.h"
#include "LhwBaseServer.h"

namespace translayor
{
class LhwServer : public BasicServer<Collectioner>
{
  public:
    LhwServer() {}
    virtual ~LhwServer() {}

    /*
    * bind() -> listen()
    * @param host 服务器地址
    * @param port 端口号
    * @param backlog 一次listen的客户端数
    */
    int32_t startBindListen(const std::string &host, int32_t port, int32_t backlog = 20) override;

    /*
    * 服务器套接字连接客户端
    * @param handler 重载虚函数
    */
    void onConnect(ConnectHandler handler)
    {
        _connectHandler = handler;
    }

    /*
    * 服务器套接字连接客户端
    * @param handler 重载纯虚函数
    */
    void onDisconnect(DisconnectHandler handler)
    {
        _disconnectIndication = handler;
    }

    /*
    * 服务器套接字连接客户端
    * @param sockfd epoll_create创建的侦听套接字
    */
    Collectioner acceptClientOfServer(int32_t sockfd) override;

  private:
    /*
    * 包括使用socket()和bind(),创建服务器套接字并绑定到指定地址和端口
    * 声明为私有,供listen调用
    * @param host 服务器地址
    * @param port 端口号
    */
   int32_t _bind(const std::string &host, int32_t port);

  private:
    
    DataSink *_dataSink; // 当有数据到来的时候,会通过数据收集器将数据发送到上层
    
    ConnectHandler _connectHandler;
    DisconnectHandler _disconnectIndication;
};

} // namespace translayor