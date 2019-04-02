#### gdb调试

```
//查看当前运行的进程
ps aux|grep a.out
//查看当前运行的轻量级进程
ps -aL|grep a.out
//查看主线程和新线程的关系
pstree -p 主线程id
```

线程栈结构查看

```
1. 获取线程ID
2. 通过命令查看栈结构 ps stack 线程ID
```

-O0 :调试命令: make CFLAGS="-g -O0" -j 4

多线程:https://blog.csdn.net/zhangye3017/article/details/80382496
