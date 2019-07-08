cmake_minimum_required(VERSION 3.7)

project(translayor)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++11 -g -O0 -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG)

include_directories(.)
include_directories(http)
include_directories(../logging)
include_directories(/usr/include/mysql)
link_directories(../logging/build)

add_library(translayor SHARED LhwCommon.cpp LhwClient.cpp LhwClientConnected.cpp LhwEpollLoop.cpp LhwServer.cpp 
LhwEpollStream.cpp LhwEventQueueLoop.cpp PackageDataSink.cpp 
LhwUserDao.cpp LhwUserDaoImp.cpp LhwChat.cpp LhwChatManager.cpp LhwDBHelper.cpp LhwOnLineDao.cpp LhwOnLineDaoImp.cpp http/LhwHttpConnection.cpp http/LhwHttpContext.cpp http/LhwHttpRequest.cpp http/LhwHttpResponse.cpp 
http/LhwHttpServer.cpp http/String.cpp)

target_link_libraries(translayor logging pthread mysqlclient)

install(TARGETS translayor DESTINATION lib)
