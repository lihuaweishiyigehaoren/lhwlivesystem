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
 * LhwEpollLoop 事件循环
 * @desc:作用:epoll的事件循环类,负责不断的监听来自epoll的事件,并对事件进行处理
 */

#pragma once

#include <sys/epoll.h>

#include <map>
#include <memory>
#include <thread>
#include <string>

#include "LhwLoop.h"
#include "LhwClientConnected.h"
#include "LhwEpollStream.h"
#include "LhwServer.h"
#include "LhwClient.h"
#include "DataSink.h"
#include "LhwLinuxEpoll.h"
#include "LhwCommon.h"

namespace translayor 
{

    class EventQueue;

    class EPollServer;

    class LhwEpollLoop : public LhwLoop 
    {

    public:

        /**
         * 静态函数,用于获取事件循环的唯一实例
         */
        static LhwEpollLoop* Get();

        virtual ~LhwEpollLoop() override;

        /*
        * 添加套接字socket对应的server键值对
        * @para socket 服务器套接字
        * @para server 服务
        */
        void addFdToServer(NativeSocket socket, LhwServer* server);

        void AddStream(EPollStreamPtr stream);

        /*
        * 在Loop中添加一个Epoll事件,是对epoll_ctl的简单封装
        * @para events 事件属性
        * @para fd 套接字
        */
        int32_t addEpollEvents(int32_t events, int32_t fd);

        /*
        * 修改loop中的epoll事件
        * @para events 事件属性
        * @para fd 套接字
        */
        int32_t modifyEpollEvents(int32_t events, int32_t fd);

    protected:

        /**
         * 私有化构造函数,外部仅有一个实例
         */
        LhwEpollLoop();

        /**
         * 重载事件循环启动函数
         */
        virtual void _run() override;

    private:

        /*
        * 初始化函数,创建io多路复用的侦听套接字
        */
        void _initialize();

        /*
        * epoll事件处理线程函数
        */
        void _processEpollEventThread();

        /*
        * 事件处理函数
        * @param eventfd epoll_create 创建的侦听套接字
        * @param events epoll_event 接受的套接字事件
        * @param nfds 接收的套接字总数
        */
        void _handleEpollEvent(int32_t eventfd, struct epoll_event* events, int32_t nfds);

        /*
        * 响应epoll中的服务器accept事件,创建与客户端的连接
        * @param eventfd 侦听套接字
        * @param listenfd 
        */
        int32_t _acceptClient(int32_t eventfd, int32_t listenfd);

        /*
        * 从客户端套接字读取数据
        * @param eventfd 侦听套接字
        * @param fd 客户端套接字
        * @param events ev 套接字监听的属性
        */
        void _read(int32_t eventfd, int32_t fd, uint32_t events);
        void _write(int32_t eventfd,int32_t fd, uint32_t events);

        void _enqueue(EPollStreamPtr connection, const char* buf, int64_t nread);

    private:

        int32_t _eventfd; // epoll文件描述符
        bool _shutdown; // 表示是否关机

        std::map<NativeSocket, LhwServer*> _servers; // 记录套接字,对应的服务器端
        std::map <NativeSocket, EPollStreamPtr> _streams; // 同一管理所有的流,便于使用套接字寻找对应的流对象
    };
}
