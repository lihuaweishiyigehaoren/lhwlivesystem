#### version1

#### 服务端

**初始化**: 创建侦听fd->eventfd

函数调用堆栈

```C++
1.translayor::IoLoop::Get()->Start(); main.cpp:19
2.EPollLoop::EPollLoop(); EPollLoop.cpp:24
3.EPollLoop::_Initialize();EPollLoop.cpp:86
4._eventfd = epoll_create(MAX_EVENT_COUNT)
```

**bind listen**:

函数调用堆栈

```c++
1.server.Listen("127.0.0.1", DefaultConnectPort); mian.cpp:26
2.EPollServer::Listen; EPollServer.cpp:56 
```

在此过程中使用socket创建了服务器fd,并绑定到了_eventfd.

**客户端连接,服务器调用堆栈**:

一个函数连接到服务器后触发accept的函数调用堆栈

```C++
translayor::IoLoop::Get()->Start(); main.cpp:19
EPollLoop::_Run(); EPoolLoop.cpp:95 通过该函数,创建分支线程接受客户端连接
EPollLoop::_EPollThread; EPoolLoop.cpp:129
EPollLoop::_HandleEvent;EPoolLoop.cpp:144
EPollLoop::_Accept;EPoolLoop.cpp:165
EPollServer::Accept;EPoolServer.cpp:93
```

连接成功,会返回一个EPollConnectionPtr对象

#### 客户端

客户端连接过程,比较简单,在此先不分析



#### 通信过程

找到read和write函数调试