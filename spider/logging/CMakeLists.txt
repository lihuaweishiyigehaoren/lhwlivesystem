cmake_minimum_required(VERSION 3.7)

project(logging)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++11 -gdwarf-2 -Og -msse3 -mavx -fPIC -DNDEBUG -DUSE_KLOG)

include_directories(.)

add_library(logging SHARED CheckLogger.cpp DirectLoggerStream.cpp ExpressionLogger.cpp IOStreamManager.cpp 
Logger.cpp Logging.cpp LogItemQueue.cpp LogOutputThread.cpp ThreadLoggerStream.cpp)

install(TARGETS logging DESTINATION lib)
