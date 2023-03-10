//
// Created by flame on 23-3-10.
//

#ifndef SERVERSECKEY_SERVEROP_H
#define SERVERSECKEY_SERVEROP_H
#include <map>
#include <string>
#include "Message.pb.h"
#include "TcpSocket.h"
using namespace std;

class ServerOp {
public:
    /*!
     * 根据配置文件读服务器配置
     * @param json 文件名
     */
    ServerOp(string json);
    /*!
     * 服务器开始工作
     */
    void startServer();
    /*!
     * 线程的回调函数
     * @param arg
     * @return
     */
    static void* working(void* arg);
    /*!
     * 密钥协商
     * @param msg 接受的消息
     * @return
     */
    string secKeyAgree(RequestMsg* msg);

    ~ServerOp();
private:
    string getRandStr(int num);
private:
    string m_serverID;
    unsigned short m_port;
    map<pthread_t,TcpSocket*> m_list;
};


#endif //SERVERSECKEY_SERVEROP_H
