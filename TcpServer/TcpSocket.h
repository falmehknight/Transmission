//
// Created by 谭颍豪 on 2023/3/6.
//

#ifndef TCPSERVER_TCPSOCKET_H
#define TCPSERVER_TCPSOCKET_H
#include<string.h>
#include<iostream>
using namespace  std;

/*
 * 创建TcoSocket对象 == 一个连接，这个对象就可以和服务器通信了，多个连接需要多个对象。
 */
class TcpSocket {
public:
    TcpSocket();
    // 传递的fd是可以直接通信的文件描述符，不需要连接操作
    explicit TcpSocket(int mSocket);

    virtual ~TcpSocket();
    // 客户端连接服务器
    int connectToHost(string ip,unsigned  short port, int timeout);
    // 发送数据
    int sendMsg(string data, int timeout);
    // 接受数据
    string recMsg(int timeout);
    // 关闭连接
    void disConnect();

    int setNonBlock(int fd);

    int setBlock(int fd);

    int readTimeout(unsigned int timeout);

    int writeTimeout(unsigned int timeout);

    int connectTimeout(struct sockaddr_in* addr, unsigned int timeout);

    int readn(void* buf,int count);

    int writen(const void* buf,int count);


private:
    int m_socket;
};


#endif //TCPSERVER_TCPSOCKET_H
