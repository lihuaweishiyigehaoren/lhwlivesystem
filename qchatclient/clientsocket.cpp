#include "clientsocket.h"
#include<string.h>
#include<QDebug>
#include"chatroom.h"
#include "LhwEpollLoop.h"


/*
函数功能：构造函数
参数：ClientSocket(QTcpSocket *socket, QObject *parent)
返回值：无
*/
ClientSocket::ClientSocket(/*QTcpSocket *socket,*/translayor::NativeSocket socket,QObject *parent)
    : QObject(parent),
      LhwEpollStream(socket)
      /*, socket(socket)*/
{
    //接收服务器返回的数据包，并执行相应的槽函数
//    QObject::connect(socket, SIGNAL(readyRead()),
    //                     this, SLOT(onReadyRead()));
}

int32_t ClientSocket::receiveData(char *buffer, int32_t bufferSize, int32_t &readSize)
{
    readSize = 0;
    int32_t nread = 0;

    // 这里用了read,后期换成linux的recv函数比较好
    while((nread = read(getSocket(),buffer + readSize,bufferSize-readSize)) > 0) // bufferSize-1指定可以接收的最大字节数
    {
        readSize += nread;
    }

    // 修改事件
    translayor::LhwEpollLoop::Get()->modifyEpollEvents(this->getEvent() | EPOLLOUT,getSocket());
//    qDebug()<< readSize;

    return nread;
}

int32_t ClientSocket::sendData(const translayor::LhwByteArray &byteArray)
{
    translayor::NativeSocket clientSocket = getSocket();

    const char* buf = byteArray.data();

    int32_t size = byteArray.size();
    int32_t n = size;

    int32_t nwrite = 0;
    while(n > 0)
    {
        nwrite = write(clientSocket, buf + size - n, n);
        if(nwrite < n)
        {
            if(nwrite == -1 && errno != EAGAIN)
            {
                qDebug() << "write data to peer failed!";
            }
            break;
        }

        n -= nwrite;
    }

    translayor::LhwEpollLoop::Get()->modifyEpollEvents(EPOLLIN | EPOLLET,clientSocket);

//    qDebug() << "woshishagou";
    // dataprocess
    User user;
    memcpy((char *)&user,buf,sizeof(User));
    dataProcess(user);
    return nwrite;
}

 // 该函数负责向服务器发起连接
 void ClientSocket::connect(const std::string& host, int32_t port)
 {
     struct sockaddr_in serv_addr;

     bzero((char*)&serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
     serv_addr.sin_port = htons(port);

     translayor::SetNonBlocking(getSocket());

     ::connect(getSocket(), (struct sockaddr*)&serv_addr, sizeof(serv_addr));
 }

 ClientConnector ClientSocket::connectToHost(const std::string& ip, int32_t port)
 {
     int32_t clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

     // Connect
     ClientConnector client = ClientConnector(new ClientSocket(clientSocket));
     client->connect(ip, port);

     // 添加事件循环
     translayor::LhwEpollLoop* ePollLoop = translayor::LhwEpollLoop::Get();

     client->setEvents(EPOLLIN | EPOLLET);
     if ( ePollLoop->addEpollEvents(client->getEvent(), clientSocket) == -1 ) // 将新创建的客户端套接字
     {
         perror("epoll_ctl: add");
         exit(EXIT_FAILURE);
     }

     ePollLoop->AddStream(client); // 将客户端对应流加入

     return client;
 }

 void ClientSocket::dataProcess(User &user)
 {
     switch(user.type)
     {
     case REG:   //注册
         emit sigReg(user);
         break;
     case LOGIN: //登录
         emit sigLogin(user);
         break;
     case ROOMNAME://刚进入时聊天列表
         emit sigRoomName(user);
         break;
     case ROOMLIST://刷新聊天室列表
         emit sigRoomList(user);
         break;
     case CHATNAME://刚进入聊天室时用户列表
         emit sigChatName(user);
         break;
     case CHATLIST://刷新用户列表
         emit sigChatList(user);
         break;
     case EXIT://退出客户端
         emit sigMasterExit(user);
         break;
     case TEXT://文字聊天
         emit sigChatText(user);
         break;
     case VIDEO://开启直播
         emit sigVideo(user);
         break;
     case UNVIDEO://关闭直播
         emit sigunVideo(user);
         break;
     case BS://弹幕
         emit sigBs(user);
         break;
     default:break;
     }
 }

