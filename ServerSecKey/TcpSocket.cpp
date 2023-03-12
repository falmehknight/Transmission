//
// Created by 谭颍豪 on 2023/3/6.
//

#include "TcpSocket.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sys/epoll.h>


TcpSocket::TcpSocket() {}

TcpSocket::TcpSocket(int mSocket) : m_socket(mSocket) {}

TcpSocket::~TcpSocket() {

}

int TcpSocket::connectToHost(string ip, unsigned short port, int timeout) {
    int ret = 0;
    if(port <=0 || port > 65535 || timeout < 0){
        ret = ParamError;
        return ret;
    }
    m_socket = socket(AF_INET,SOCK_STREAM,0);
    if(m_socket < 0){
        ret = errno;
        cout<<"func socket() err:"<<ret<<endl;
        return ret;
    }
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;  //设置为ipv4
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip.data());

    ret = connectTimeout((struct sockaddr_in*)(&servaddr),(unsigned int) timeout);
    if(ret <0){
        if(ret == -1 &&errno == ETIMEDOUT){
            ret = TimeoutError;
            return ret;
        }
        else {
            cout<<"connectTimeout errno:"<<errno<<endl;
            return errno;
        }
    }
    return ret;
}

int TcpSocket::sendMsg(string data, int timeout) {
    int ret = writeTimeout(timeout); //-1 on behalf of timeout
    int hasWrite = 0;
    if(ret == 0){

        int dataLen = data.size()+4;
        // 添加4字节作为头部，存储块的长度
        unsigned char * netData = (unsigned char *)malloc(dataLen);
        if(netData == nullptr){
            ret = MallocError;
            cout<<"func sckClient_send() malloc Err:"<<ret<<endl;
            return ret;
        }
        //转换成网络字节序
        int netLen = htonl(data.size());
        memcpy(netData,&netLen,4);
        memcpy(netData+4,data.data(),data.size());

        //没问题的话返回发送的实际字节数，失败返回-1
        hasWrite = writen(netData,dataLen);
        cout<<"发送了"<<hasWrite<<"的数据"<<endl;
        if(hasWrite < dataLen){ //失败
            if(netData != nullptr){
                free(netData);
                netData = nullptr;
            }
            return hasWrite;
        }
        if(netData != nullptr){
            free(netData);
            netData = nullptr;
        }
    }
    else {
        if (ret == -1 && errno == ETIMEDOUT)
        {
            ret = TimeoutError;
            printf("func sckClient_send() mlloc Err:%d\n ", ret);
        }
    }
    return ret;
}

string TcpSocket::recMsg(int timeout) {
    int ret = readTimeout(timeout);
    if(ret != 0){
        if (ret == -1 || errno == ETIMEDOUT)
        {
            cout<<"readTimeout(timeout) err: TimeoutError"<<endl;
            return string();
        }
        else
        {
            cout<<"readTimeout(timeout) err:"<<ret<<endl;
            return string();
        }
    }
    int netDataLen = 0;
    ret = readn(&netDataLen,4);
    if (ret == -1)
    {
        cout<<"func readn() err:"<<ret<<endl;
        return string();
    }
    else if (ret < 4)
    {
        cout<<"func readn() err peer closed:"<<ret<<endl;
        return string();
    }
    int n = ntohl(netDataLen);
    n = n;//这里是减去头部的4字节长度
    char * buf = (char*) malloc(n+1);
    if(buf == nullptr){
        ret = MallocError;
        cout<<"malloc() Err:"<<ret<<endl;
        return nullptr;
    }
    ret = readn(buf,n);
    if(ret == -1){
        cout<<"func readn() err:"<<ret<<endl;
        return string();
    }
    else if(ret < n){
        cout<<"func readn() err peer closed:"<<ret<<endl;
        return string();
    }
    buf[n] ='\0';
    string data = string(buf);
    free(buf);
    return data;
}

void TcpSocket::disConnect() {

    if(m_socket >= 0) close(m_socket);
}

int TcpSocket::setNonBlock(int fd) {
    int flags = fcntl(fd,F_GETFL);
    if(-1 == flags) return flags;
    flags |= O_NONBLOCK;
    int ret = fcntl(fd,F_SETFL,flags);
    return ret;
}

int TcpSocket::setBlock(int fd) {
    int flags = fcntl(fd,F_GETFL);
    if(-1 == flags) return flags;
    flags &= ~O_NONBLOCK;
    int ret = fcntl(fd,F_SETFL,flags);
    return ret;
}

int TcpSocket::readTimeout(unsigned int timeout) {
    int ret = 0;
    if(timeout>0){
        // 上树
        int epfd = epoll_create(1);
        struct epoll_event ev;
        ev.data.fd = m_socket;
        ev.events = EPOLLIN;
        ret = epoll_ctl(epfd,EPOLL_CTL_ADD,m_socket,&ev); // -1错误，0成功
        if(ret <0) return -1;
        //监听
        do{
            ret = epoll_wait(epfd,&ev,1,timeout); // 0超时，-1错误
        }while(ret<0 && errno == EINTR);
        // 超时
        if (ret == 0)
        {
            ret = -1;
            errno = ETIMEDOUT;
        }
        else if (ret == 1)
        {
            ret = 0;	// 没超时
        }
    }
    return ret;
}

int TcpSocket::writeTimeout(unsigned int timeout) {
    int ret = 0;
    if (timeout > 0)
    {
        int epfd = epoll_create(1);
        struct epoll_event ev;
        ev.data.fd = m_socket;
        ev.events = EPOLLOUT;
        ret = epoll_ctl(epfd,EPOLL_CTL_ADD,m_socket,&ev); // -1错误，0成功
        if(ret <0) return -1;
        //监听
        do{
            ret = epoll_wait(epfd,&ev,1,timeout); // 0超时，-1错误
        }while(ret<0 && errno == EINTR);
        if (ret == 0)
        {
            ret = -1;
            errno = ETIMEDOUT;
        }
        else if (ret == 1)
        {
            ret = 0;
        }
    }

    return ret;
}

int TcpSocket::connectTimeout(struct sockaddr_in *addr, unsigned int timeout) {
    int ret;
    socklen_t addrLen = sizeof(struct sockaddr_in);

    if(timeout>0) setNonBlock(m_socket);
    ret = connect(m_socket,(struct sockaddr*)addr,addrLen);
    // 非阻塞连接，返回-1,并且errno为EINPROGRESS，表示连接还在进行中
    if(ret <0 && errno == EINPROGRESS){
        fd_set connectFdSet;
        struct timeval times;
        FD_ZERO(&connectFdSet);
        FD_SET(m_socket,&connectFdSet);
        times.tv_sec = timeout;
        times.tv_usec = 0;
        do{
            ret = select(m_socket+1,nullptr,&connectFdSet, nullptr,&times);
        }while(ret<0 && errno == EINTR); //遇到中断则继续

        if(ret ==0){
            // 超时
            ret = -1;
            errno = ETIMEDOUT;
        }
        else if(ret <0){
            return -1;
        }
        else if(ret == 1){
            // ret返回为1,可能有两种情况，一种是连接建立成功，一种是套接字错误
            int err = 0;
            socklen_t socklen = sizeof(err);
            int sockOptRet = getsockopt(m_socket,SOL_SOCKET,SO_ERROR,&err,&socklen);
            if(sockOptRet == -1) return -1;
            if(err == 0) ret = 0; //success
            else{
                errno = err;
                ret = -1;
            }
        }

    }
    if(timeout > 0) setBlock(m_socket);

    return ret;
}

int TcpSocket::readn(void *buf, int count) {
    size_t nleft = count;
    ssize_t nread;
    char *bufp = (char*)buf;

    while (nleft > 0)
    {
        if ((nread = read(m_socket, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            return -1;
        }
        else if (nread == 0)
        {
            return count - nleft;
        }

        bufp += nread;
        nleft -= nread;
    }

    return count;
}

int TcpSocket::writen(const void *buf, int count) {
    size_t nleft = count;
    ssize_t nwritten;
    char *bufp = (char*)buf;

    while (nleft > 0)
    {
        if ((nwritten = write(m_socket, bufp, nleft)) < 0)
        {
            if (errno == EINTR)	// 被信号打断
            {
                continue;
            }
            return -1;
        }
        else if (nwritten == 0)
        {
            continue;
        }

        bufp += nwritten;
        nleft -= nwritten;
    }

    return count;
}
