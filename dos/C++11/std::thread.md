#### std::thread

C++11并发之线程

https://www.cnblogs.com/lidabo/p/7852033.html

易懂

https://www.cnblogs.com/lifan3a/articles/7538472.html



join() 和 detach()

join()等待子线程执行完之后,主线程才可以执行下去,此时主线程会释放掉执行完的子线程资源

detach()将子线程从主线程分离,子线程执行完成后会自己释放掉资源。分离后的线程，主线程将对它没有控制权了

