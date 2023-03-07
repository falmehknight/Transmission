cmake_minimum_required(VERSION 3.23)
project(TcpServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(TcpServer main.cpp TcpServer.cpp TcpServer.h TcpSocket.cpp TcpSocket.h)
