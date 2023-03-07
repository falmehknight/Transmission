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

TcpServer::TcpServer(int mLfd) : m_lfd(mLfd) {

}

TcpServer::~TcpServer() {

}

TcpServer::TcpServer() {

}

int TcpServer::setListen(unsigned short port) {
    int ret = 0;
    return 0;
}

void TcpServer::closeFd() {

}

TcpSocket *TcpServer::acceptConn(int timeout) {
    return nullptr;
}
