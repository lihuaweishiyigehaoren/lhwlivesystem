cmake_minimum_required(VERSION 3.7)

project(chatclient)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++11 -g -O0 -msse3 -mavx -fPIC -DNDEBUG -DOS_LINUX -DUSE_KLOG)

include_directories(.)
include_directories(../spider/logging)
include_directories(../spider/translayor)
include_directories(../spider/translayor/http)
link_directories(../spider/logging/lib)
link_directories(../spider/translayor/lib)

add_executable(chatclient main.cpp)

target_link_libraries(chatclient logging translayor pthread)
