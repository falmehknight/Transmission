//
// Created by 谭颍豪 on 2023/3/6.
//

#ifndef TCPSERVER_TCPSERVER_H
#define TCPSERVER_TCPSERVER_H


#include "TcpSocket.h"

// 服务器端不负责通信，只负责监听，如果通信则使用客户端类，即socket类
class TcpServer {
private:
    int m_lfd;  //监听的文件描述符
public:
    /*!
     * 如果已经有了监听的文件描述符，可以直接传入其中
     * @param mLfd
     */
    explicit TcpServer(int mLfd);
    /*!
     *  初始化监听的套接字：创建，绑定，监听
     */
    TcpServer();
    /*!
     *
     */

    virtual ~TcpServer();
    /*!
     *  设置监听
     * @param port:端口
     * @return
     */
    int setListen(unsigned short port);

    /*!
     * 等待并接受客户端连接请求
     * @param timeout：连接超时时间
     * @return 返回一个已建立连接的socket
     */
    TcpSocket * acceptConn(int timeout);

    /*!
     *
     */
    void closeFd();


};


#endif //TCPSERVER_TCPSERVER_H
