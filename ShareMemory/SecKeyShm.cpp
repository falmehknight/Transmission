//
// Created by flame on 23-3-8.
//

#include "SecKeyShm.h"

SecKeyShm::SecKeyShm(int key, int maxNode) : BaseShm(key, maxNode*sizeof(NodeSHMInfo)),m_maxNode(maxNode) {

}

SecKeyShm::SecKeyShm(string name, int maxNode) : BaseShm(name, maxNode*sizeof(NodeSHMInfo),m_maxNode(maxNode)) {

}

SecKeyShm::~SecKeyShm() {

}

void SecKeyShm::shmInit() {
    if(m_shmAddr !=nullptr){
        memset(m_shmAddr,0,m_maxNode*sizeof(NodeSHMInfo));
    }
}

int SecKeyShm::shmWrite(NodeSHMInfo *pNodeInfo) {
    int ret = -1;
    NodeSHMInfo* pAddr = static_cast<NodeSHMInfo*>(mapShm());
    if(pAddr == nullptr) return ret;
    NodeSHMInfo* pNode = nullptr;
    // 判断传入的网点密钥是否已经存在
    for(int i=0;i<m_maxNode;i++){
        //pNode依次指向每个节点的首地址
        pNode = pAddr+i;
        if(strcmp(pNode->clientID,pNodeInfo->clientID) == 0 && strcmp(pNode->serverID,pNodeInfo->serverID) ==0 ){
            memcpy(pNode,&pNodeInfo,sizeof(NodeSHMInfo));
            unmapShm();
            cout<<"写数据成功:原数据被覆盖"<<endl;
            return 0;
        }
    }
    //如果没找到对应的信息，找一个空地方放入
    int i =0;
    NodeSHMInfo tmpNode;
    for(i=0;i<m_maxNode;i++){
        pNode = pAddr+1;
        if(memcmp(&tmpNode,pNode,sizeof(NodeSHMInfo))==0){
            ret = 0;
            memcpy(pNode,pNodeInfo, sizeof(NodeSHMInfo));
            cout<<"写数据成功：在新的节点添加了数据"<<endl;
            break;
        }
    }
    if(i = m_maxNode) ret = -1;
    unmapShm();
    return ret;
}

int SecKeyShm::shmRead(string clientID, string serverID, NodeSHMInfo *pNodeInfo) {
    int ret = -1;
    // 关联共享内存
    NodeSHMInfo *pAddr = NULL;
    pAddr = static_cast<NodeSHMInfo*>(mapShm());
    if (pAddr == NULL)
    {
        cout << "共享内存关联失败..." << endl;
        return ret;
    }
    cout << "共享内存关联成功..." << endl;

    //遍历网点信息
    int i = 0;
    NodeSHMInfo	*pNode = NULL;
    // 通过clientID和serverID查找节点
    cout << "maxNode: " << m_maxNode << endl;
    for (i = 0; i < m_maxNode; i++)
    {
        pNode = pAddr + i;
        cout << i << endl;
        cout << "clientID 比较: " << pNode->clientID << ", " << clientID.data() << endl;
        cout << "serverID 比较: " << pNode->serverID << ", " << serverID.data() << endl;
        if (strcmp(pNode->clientID, clientID.data()) == 0 &&
            strcmp(pNode->serverID, serverID.data()) == 0)
        {
            // 找到的节点信息, 拷贝到传出参数
            pNodeInfo = pNode;
            cout << "++++++++++++++" << endl;
            cout << pNodeInfo->clientID << " , " << pNodeInfo->serverID << ", "
                 << pNodeInfo->secKey << ", " << pNodeInfo->status << ", "
                 << pNodeInfo->secKey << endl;
            cout << "===============" << endl;
            ret = 0;
            break;
        }
    }
    unmapShm();
    return ret;
}
