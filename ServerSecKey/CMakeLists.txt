cmake_minimum_required(VERSION 3.24)
project(ServerSecKey)

set(CMAKE_CXX_STANDARD 17)
link_directories(/usr/lib)
link_directories(/usr/local/lib)
add_executable(ServerSecKey main.cpp ServerOp.cpp TcpServer.h TcpServer.cpp Codec.cpp CodecFaCctory.cpp Hash.cpp Message.pb.cc RequestCodec.cpp RequestFactory.cpp ResponseCodec.cpp ResponseFactory.cpp RsaCrypto.cpp TcpSocket.cpp MysqlOP.h MysqlOP.cpp SecKeyNodeInfo.h)

target_link_libraries(${PROJECT_NAME} jsoncpp protobuf pthread crypto)