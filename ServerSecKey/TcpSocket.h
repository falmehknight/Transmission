//
// Created by 谭颍豪 on 2023/3/6.
//

#ifndef TCPSERVER_TCPSOCKET_H
#define TCPSERVER_TCPSOCKET_H
#include<string.h>
#include<iostream>
using namespace  std;

static const int TIMEOUT = 10000;
/*!
 * 用于通信的套接字类
 */
class TcpSocket {
public:
    enum ErrorType {ParamError = 3001, TimeoutError, PeerCloseError, MallocError}; //出错类型
    TcpSocket();
    /*!
     * 使用一个可以通信的套接字实例化套接字对象
     * @param mSocket  传递的fd是可以直接通信的文件描述符，不需要连接操作
     */
    explicit TcpSocket(int mSocket);

    virtual ~TcpSocket();
    /*!
     * 客户端连接服务器
     * @param ip
     * @param port
     * @param timeout
     * @return 0成功，其他值均为失败。
     */
    int connectToHost(string ip,unsigned short port, int timeout = TIMEOUT);
    /*!
     *  发送数据
     * @param data
     * @param timeout
     * @return
     */
    int sendMsg(string data, int timeout = TIMEOUT);

    /*!
     *  接受数据
     * @param timeout
     * @return
     */
    string recMsg(int timeout = TIMEOUT);
    /*!
     * 关闭连接
     */
    void disConnect();


private:
    /*!
     * 设置IO为非阻塞模式
     * @param fd
     * @return
     */
    int setNonBlock(int fd);
    /*!
     * 设置IO为阻塞模式
     * @param fd
     * @return
     */
    int setBlock(int fd);
    /*!
     * 读超时检测函数，不包含读操作
     * @param timeout
     * @return 成功（未超时）返回0，失败返回-1，超时返回-1并且errno = ETIMEDOUT
     */
    int readTimeout(unsigned int timeout);
    /*!
     * 写超时检测函数，不包含写操作
     * @param timeout
     * @return 成功（未超时）返回0，失败返回-1，超时返回-1并且errno = ETIMEDOUT
     */
    int writeTimeout(unsigned int timeout);
    /*!
     * 带连接超时的connect函数
     * @param addr
     * @param timeout
     * @return 成功（未超时）返回0，失败返回-1，超时返回-1并且errno = ETIMEDOUT
     */
    int connectTimeout(struct sockaddr_in* addr, unsigned int timeout);
    /*!
     * 每次从缓冲区读取n个字符
     * @param buf
     * @param count
     * @return 成功返回count，失败返回-1，读到EOF返回<count
     */
    int readn(void* buf,int count);
    /*!
     * 每次往缓冲区写入n个字符
     * @param buf
     * @param count
     * @return 成功返回count，失败返回-1
     */
    int writen(const void* buf,int count);
private:
    int m_socket;  //用于通信的套接字
};


#endif //TCPSERVER_TCPSOCKET_H
