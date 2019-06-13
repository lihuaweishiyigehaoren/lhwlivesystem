cmake_minimum_required(VERSION 3.7)

project(logging)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_library(logging SHARED CheckLogger.cpp DirectLoggerStream.cpp ExpressionLogger.cpp IOStreamManager.cpp 
Logger.cpp Logging.cpp LogItemQueue.cpp LogOutputThread.cpp ThreadLoggerStream.cpp)

install(TARGETS logging DESTINATION lib)
