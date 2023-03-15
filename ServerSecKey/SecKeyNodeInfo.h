//
// Created by flame on 23-3-14.
//

#ifndef SERVERSECKEY_SECKEYNODEINFO_H
#define SERVERSECKEY_SECKEYNODEINFO_H
#include <string.h>

class NodeSecKeyInfo{
public:
    NodeSecKeyInfo():status(0),secKeyID(0){
        bzero(clientID,sizeof(clientID));
        bzero(serverID,sizeof(serverID));
        bzero(secKey,sizeof(secKey));
    }
    int status;   // 密钥的状态，1可用，0不可用
    int secKeyID; // 密钥的编号
    char clientID[12]; // 客户端ID，客户端的标识
    char serverID[12]; // 服务器ID，服务器的标识
    char secKey[128]; // 对称加密的密钥
};
#endif //SERVERSECKEY_SECKEYNODEINFO_H
