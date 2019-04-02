#### gdb 调试问题总结

**问题1**:./chatserver: error while loading shared libraries: libtranslayor.so: cannot open shared object file: No such file or directory

解决方法: 新建文件buildgdb.sh

内容为:

```
export LD_LIBRARY_PATH="../../../spider/logging/target/lib":$LD_LIBRARY_PATH
export LD_LIBRARY_PATH="../../../spider/translayor/target/lib":$LD_LIBRARY_PATH
gdb chatserver
```

**问题2:**调试进入之后,无法打印变量No symbol "port" in current context.

解决方法:编译选项问题.https://blog.csdn.net/riopho/article/details/80593125