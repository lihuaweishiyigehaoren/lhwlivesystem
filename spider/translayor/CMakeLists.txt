cmake_minimum_required(VERSION 3.7)

project(translayor)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(http)
include_directories(../logging)
link_directories(../logging/build)

add_library(translayor SHARED CommonUtils.cpp EPollClient.cpp EPollConnection.cpp EPollLoop.cpp EPollServer.cpp 
EPollStream.cpp EventQueueLoop.cpp Net.cpp PackageDataSink.cpp ServerSample.cpp ThreadPool.cpp 
http/HttpConnection.cpp http/HttpContext.cpp http/HttpRequest.cpp http/HttpResponse.cpp 
http/HttpServer.cpp http/String.cpp)

target_link_libraries(translayor logging)

install(TARGETS translayor DESTINATION lib)
