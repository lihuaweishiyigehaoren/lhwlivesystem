#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
//#include<QTcpSocket>
#include "LhwUser.h"
#include "LhwEpollStream.h"
//#include "LhwClient.h"

class ClientSocket;
typedef std::shared_ptr<ClientSocket> ClientConnector;
class ClientSocket : public QObject, public translayor::LhwEpollStream
{
    Q_OBJECT
public:
    explicit ClientSocket(/*QTcpSocket *socket, */translayor::NativeSocket socket,QObject *parent = 0);

    virtual int32_t receiveData(char* buffer, int32_t bufferSize, int32_t& readSize) override;
    virtual int32_t sendData(const translayor::LhwByteArray& byteArray) override;

    void connect(const std::string& host, int32_t port);
    static ClientConnector connectToHost(const std::string& ip, int32_t port);

    void dataProcess(User &user) override;

signals:
    void sigReg(User user);//注册
    void sigLogin(User user);//登录
    void sigRoomName(User user);//房间名
    void sigRoomList(User user);//房间列表
    void sigChatName(User user);//聊天室用户
    void sigChatList(User user);//聊天室用户列表
    void sigMasterExit(User user);//房主退出
    void sigChatText(User user);//文字聊天
    void sigVideo(User user);//视频
    void sigunVideo(User user);//关闭视频
    void sigBs(User user);//弹幕
private:
//    QTcpSocket *socket;
};

#endif // CLIENTSOCKET_H
