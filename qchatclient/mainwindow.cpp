#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHostAddress>
#include<string.h>
#include<QDebug>
#include "LhwUser.h"
#include<QByteArray>
#include"clientsocket.h"
#include<QThread>
#include<QMetaType>

#include "LhwIOLoopConfig.h"

/*
函数功能：构造函数
参数：QWidget *parent
返回值：无
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet ("background-image:url(:/image/image/pic1.jpg)");
    ui->name->setStyleSheet ("background-image:url()");
    ui->passwd->setStyleSheet ("background-image:url()");
    ui->login->setFlat (true);
    ui->reg->setFlat (true);

    ui->login->setStyleSheet("border-radius:10px;padding:2px 4px;");
    ui->reg->setStyleSheet("border-radius:10px;padding:2px 4px;");

//    socket = new QTcpSocket(this);
//    //连接服务器出错时执行槽函数
//    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
//                     this, SLOT(onError(QAbstractSocket::SocketError)));

    qRegisterMetaType<User>("User");        //向Qt注册User结构体

    translayor::IoLoop::Get()->Start();
    cs = ClientSocket::connectToHost("127.0.0.1", 8080);

//    QThread *th = new QThread();

//    //连接断开时删除子线程的内存
//    QObject::connect(socket, SIGNAL(disconnected()),
//                    cs, SLOT(deleteLater()));
//    //连接断开时结束子线程
//    QObject::connect(socket, SIGNAL(disconnected()),
//                    th, SLOT(quit()));

    // 接收到子线程返回的注册信息
    QObject::connect(cs.get(),SIGNAL(sigReg(User)),
                     this, SLOT(onSigReg(User)));

    //接收到子线程返回的登录信息
    QObject::connect(cs.get(), SIGNAL(sigLogin(User)),
                     this, SLOT(onSigLogin(User)));

//    cs->moveToThread(th);   //客户端创建线程，在子线程执行读操作

//    QObject::connect(th,SIGNAL(finished()),
//                     cs.get(),SLOT(deleteLater()));

//    th->start();

}


/*
函数功能：析构函数
参数：无
返回值：无
*/
MainWindow::~MainWindow()
{
    delete ui;
}


/*
函数功能：网络链接错误处理
参数：QAbstractSocket::SocketError socketError
返回值：无
*/
//void MainWindow::onError(QAbstractSocket::SocketError socketError)
//{
//    box.warning(this, "警告", "连接服务器失败");
//}


/*
函数功能：注册按钮
参数：无
返回值：无
*/
void MainWindow::on_reg_clicked()
{
    User user;
    memset(&user, 0, sizeof(User));
    QString name = ui->name->text();
    if(name.isEmpty())
    {
        box.warning(this, "警告", "请输入用户名");
        return;
    }
    ui->name->clear();
    char* pname = name.toLocal8Bit().data();
    strncpy(user.username, pname, 20);

    QString passwd = ui->passwd->text();
    if(passwd.isEmpty())
    {
        box.warning(this, "警告", "请输入密码");
        return;
    }
    ui->passwd->clear();
    char* ppasswd = passwd.toLocal8Bit().data();
    strncpy(user.userpasswd, ppasswd, 20);
    user.type = REG;
    cs->sendData(translayor::LhwByteArray((char*)&user,static_cast<int32_t>(sizeof(user))));
}


/*
函数功能：登录按钮
参数：无
返回值：无
*/
void MainWindow::on_login_clicked()
{
//    User user;
//    memset(&user, 0, sizeof(User));
//    QString name = ui->name->text();
//    ui->name->clear();
//    char* pname = name.toLocal8Bit().data();
//    strncpy(user.username, pname, 20);

//    QString passwd = ui->passwd->text();
//    ui->passwd->clear();
//    char* ppasswd = passwd.toLocal8Bit().data();
//    strncpy(user.userpasswd, ppasswd, 20);
//    user.type = LOGIN;
//    socket->write((char*)&user, sizeof(user));
}


/*
函数功能：注册
参数：User user
返回值：无
*/
void MainWindow::onSigReg(User user)
{
    QString text = user.data;
    if(text != "注册成功")
    {
        box.warning(this, "警告", text);
    }
    else
    {
        box.information(this, "提示", text);
    }
}


/*
函数功能：登录
参数：User user
返回值：无
*/
void MainWindow::onSigLogin(User user)
{
    //    QString text = user.data;
    //    if(text != "登陆成功"){
    //        box.warning(this, "警告", text);
    //    }
    //    else{
    //        box.information(this, "提示", text);
    //        dialog = new Dialog(cs, socket, user, this);

    //        QString str = QString::fromLocal8Bit (user.username);
    //        str += ", 欢迎来到江山悦播";
    //        dialog->setWindowTitle (str);
    //        this->hide();
    //        dialog->show();
    //    }
}
