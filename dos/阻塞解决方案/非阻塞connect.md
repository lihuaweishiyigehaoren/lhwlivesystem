```
实现非阻塞 connect ，首先把 sockfd 设置成非阻塞的。这样调用
connect 可以立刻返回，根据返回值和 errno 处理三种情况：
(1) 如果返回 0，表示 connect 成功。
(2) 如果返回值小于 0， errno 为 EINPROGRESS,  表示连接
      建立已经启动但是尚未完成。这是期望的结果，不是真正的错误。
(3) 如果返回值小于0，errno 不是 EINPROGRESS，则连接出错了。
```

https://blog.csdn.net/liangxiaozhang/article/details/17410141(讲的是errno返回值的代表的错误)
