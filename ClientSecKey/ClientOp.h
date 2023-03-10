//
// Created by flame on 23-3-10.
//

#ifndef CLIENTSECKEY_CLIENTOP_H
#define CLIENTSECKEY_CLIENTOP_H
#include<string>
using namespace  std;
struct ClientInfo{
    string serverID;
    string clientID;
    string ip;
    unsigned short port;
};

class ClientOp {
public:
    /*!
     * 根据配置文件初始化客户端的信息
     * @param jsonFile json文件名
     */
    ClientOp(string jsonFile);
    ~ClientOp();
    /*!
     * 密钥协商
     * @return
     */
    bool secKeyAgree();
    /*!
     * 密钥校验
     * @return
     */
    bool secKeyCheck();
    /*!
     * 密钥注销
     * @return
     */
    bool secKeyLogout();

private:
    ClientInfo m_info; //客户端信息
};


#endif //CLIENTSECKEY_CLIENTOP_H
