cmake_minimum_required(VERSION 3.24)
project(ServerSecKey)

set(CMAKE_CXX_STANDARD 17)

add_executable(ServerSecKey main.cpp ServerOp.cpp TcpServer.h TcpServer.cpp)
