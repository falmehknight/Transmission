//
// Created by flame on 23-3-8.
//

#ifndef SHAREMEMORY_SECKEYSHM_H
#define SHAREMEMORY_SECKEYSHM_H
#include "BaseShm.h"
#include <string.h>

class NodeSHMInfo{

public:
    NodeSHMInfo() : status(0),secKeyID(0){
        bzero(clientID, sizeof(clientID));
        bzero(secKey,sizeof(secKey));
        bzero(serverID,sizeof(serverID));
    }
    int status;  //密钥的状态，1可以用，0：不可用
    int secKeyID; // 密钥的编号
    char clientID[12]; // 客户端的ID
    char serverID[12]; // 服务端的ID
    char secKey[128]; // 对称加密的密钥
};

class SecKeyShm : public BaseShm{
public:
    /*!
     * 根据给定的key和最大节点数构造共享内存
     * @param key
     * @param maxNode
     */
    SecKeyShm(int key,int maxNode);
    /*!
     * 根据路径和最大节点数构造共享内存
     * @param name
     * @param maxNode
     */
    SecKeyShm(string name,int maxNode);

    ~SecKeyShm();
    /*!
     * 将共享内存清空
     */
    void shmInit();
    /*!
     * 往共享内存中write
     * @param pNodeInfo
     * @return -1 失败，0 成功
     */
    int shmWrite(NodeSHMInfo* pNodeInfo);
    /*!
     *
     * @param clientID  客户端ID
     * @param serverID  服务端ID
     * @param pNodeInfo 一块数据（传出）
     * @return  -1 失败，0 成功
     */
    int shmRead(string clientID, string serverID, NodeSHMInfo* pNodeInfo);
private:
    int m_maxNode;
};


#endif //SHAREMEMORY_SECKEYSHM_H
