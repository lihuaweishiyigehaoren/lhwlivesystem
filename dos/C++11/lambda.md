#### lambda

详细讲解:

https://www.cnblogs.com/DswCnblog/p/5629165.html



举例子(在该项目中)

```c++
server.OnConnect([=](translayor::IStream* stream){
    stream->OnData(packageDataSink->StreamDataHandler(stream));
});
```

隐式捕获有两种方式，分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量。

OnConnect()中的内容为lambda表达式,返回的是以(translayor::IStream* stream)为参数,stream->OnData(packageDataSink->StreamDataHandler(stream));为函数体的函数名