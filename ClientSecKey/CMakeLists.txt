cmake_minimum_required(VERSION 3.24)
project(ClientSecKey)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ClientSecKey
        ClientOp.cpp
        ClientOp.h main.cpp Hash.h Hash.cpp RsaCrypto.h RsaCrypto.cpp Codec.cpp CodecFaCctory.cpp RequestCodec.cpp RequestFactory.cpp Message.pb.cc TcpServer.h TcpSocket.cpp TcpServer.cpp ResponseFactory.h ResponseFactory.cpp ResponseCodec.cpp)
