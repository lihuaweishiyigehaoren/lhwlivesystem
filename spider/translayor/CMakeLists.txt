cmake_minimum_required(VERSION 3.7)

project(translayor)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++11 -g -O0 -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG)

include_directories(.)
include_directories(http)
include_directories(../logging)
link_directories(../logging/build)

add_library(translayor SHARED CommonUtils.cpp EPollClient.cpp LhwClientConnected.cpp LhwEpollLoop.cpp LhwServer.cpp 
EPollStream.cpp LhwEventQueueLoop.cpp Net.cpp PackageDataSink.cpp ServerSample.cpp ThreadPool.cpp 
http/HttpConnection.cpp http/HttpContext.cpp http/HttpRequest.cpp http/HttpResponse.cpp 
http/HttpServer.cpp http/String.cpp)

target_link_libraries(translayor logging pthread)

install(TARGETS translayor DESTINATION lib)
