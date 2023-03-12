cmake_minimum_required(VERSION 3.24)
project(ClientSecKey)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_directories(/usr/lib)
link_directories(/usr/local/lib)

add_executable(ClientSecKey
        ClientOp.cpp
        main.cpp Hash.cpp RsaCrypto.h RsaCrypto.cpp Codec.cpp CodecFaCctory.cpp RequestCodec.cpp RequestFactory.cpp Message.pb.cc  TcpSocket.cpp TcpServer.cpp ResponseFactory.h ResponseFactory.cpp ResponseCodec.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp protobuf pthread crypto)