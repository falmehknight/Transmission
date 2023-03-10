//
// Created by 谭颍豪 on 2023/3/6.
//

#include "TcpServer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

TcpServer::TcpServer(int mLfd) : m_lfd(mLfd) {

}

TcpServer::~TcpServer() {

}

TcpServer::TcpServer() {

}

int TcpServer::setListen(unsigned short port) {
    int ret = 0;
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(sockaddr_in));
    servaddr.sin_family = AF_INET;  //设置为ipv4
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // create listen socket
    this->m_lfd = socket(AF_INET,SOCK_STREAM,0);
    if(m_lfd == -1){
        ret =errno;
        return ret;
    }
    int on = 1;
    // port reuse
    ret = setsockopt(m_lfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(ret == -1){
        ret =errno;
        return ret;
    }
    //监听的socket bind ip and port
    ret = bind(m_lfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret == -1){
        ret =errno;
        return ret;
    }
    ret = listen(m_lfd,128);
    if(ret == -1){
        ret =errno;
        return ret;
    }
    return 0;
}

void TcpServer::closeFd() {
    close(m_lfd);
}

TcpSocket *TcpServer::acceptConn(int timeout ) {
    int ret;
    if(timeout>0){
        // 上树
        int epfd = epoll_create(1);
        struct epoll_event ev;
        ev.data.fd = m_lfd;
        ev.events = EPOLLIN;
        ret = epoll_ctl(epfd,EPOLL_CTL_ADD,m_lfd,&ev); // -1错误，0成功
        if(ret <0) return nullptr;
        //监听
        do{
            ret = epoll_wait(epfd,&ev,1,timeout); // 0超时，-1错误
        }while(ret<0 && errno == EINTR);
        if(ret<=0) return nullptr;
    }
    //调用accept 因为前面已经通过epoll_wait验证了有变化，所以这里不会被阻塞.
    struct sockaddr_in addrCli;
    socklen_t addrLen = sizeof(struct sockaddr_in);
    int connFd = accept(m_lfd,(struct sockaddr*)&addrCli,&addrLen);
    if(-1 == connFd) return nullptr;
    return new TcpSocket(connFd);
}
