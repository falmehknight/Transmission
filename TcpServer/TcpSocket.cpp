//
// Created by 谭颍豪 on 2023/3/6.
//

#include "TcpSocket.h"


TcpSocket::TcpSocket() {}

TcpSocket::TcpSocket(int mSocket) : m_socket(mSocket) {}

TcpSocket::~TcpSocket() {

}

int TcpSocket::connectToHost(string ip, unsigned short port, int timeout) {
    return 0;
}

int TcpSocket::sendMsg(string data, int timeout) {
    return 0;
}

string TcpSocket::recMsg(int timeout) {
    return nullptr;
}

void TcpSocket::disConnect() {

}

int TcpSocket::setNonBlock(int fd) {
    return 0;
}

int TcpSocket::setBlock(int fd) {
    return 0;
}

int TcpSocket::readTimeout(unsigned int timeout) {
    return 0;
}

int TcpSocket::writeTimeout(unsigned int timeout) {
    return 0;
}

int TcpSocket::connectTimeout(struct sockaddr_in *addr, unsigned int timeout) {
    return 0;
}

int TcpSocket::readn(void *buf, int count) {
    return 0;
}

int TcpSocket::writen(const void *buf, int count) {
    return 0;
}
