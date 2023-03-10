//
// Created by flame on 23-3-10.
//

#include <fstream>
#include <json/json.h>
#include "ServerOp.h"
#include "TcpServer.h"
#include "ResponseCodec.h"
#include "ResponseFactory.h"
#include "RsaCrypto.h"
#include "Hash.h"
using namespace Json;

ServerOp::ServerOp(string json) {
    ifstream ifs(json);
    Reader reader;
    Value root;
    reader.parse(ifs,root);

    m_serverID = root["ServerID"].asString();
    m_port = root["Port"].asInt();
}

void ServerOp::startServer() {
    TcpServer* server = new TcpServer();
    server->setListen(m_port);
    while(1){
        cout << "等待客户端连接..." << endl;
        TcpSocket* tcp = server->acceptConn();
        if(tcp == nullptr) continue;
        cout << "客户端连接成功..." << endl;
        // 创建子进程
        pthread_t tid;
        pthread_create(&tid, nullptr,working,this);
        m_list.insert(make_pair(tid,tcp));
    }
}

void *ServerOp::working(void *arg) {
    sleep(1);
    ServerOp* op = static_cast<ServerOp *>(arg);
    // 1. 接收客户端数据 -> 编码
    TcpSocket* tcp = op->m_list[pthread_self()];
    string msg = tcp->recMsg();

    // 2. 反序列化 -> 得到原始数据 RequestMsg 类型
    CodecFaCctory* factory = new ResponseFactory(msg);
    Codec* c = factory->createCodec();
    RequestMsg* req = (RequestMsg*)c->decodeMsg();

    // 3. 取出数据
    // 判断客户端是什么请求
    string data;
    switch (req->cmdtype())
    {
        case 1:
            // 秘钥协商
            data = op->secKeyAgree(req);
            break;
        case 2:
            // 秘钥校验
            break;
        default:
            break;
    }
    tcp->sendMsg(data);

    return NULL;
}

string ServerOp::secKeyAgree(RequestMsg *msg) {
    ResponseInfo info;
    ofstream ofs("public.pem");
    ofs << msg->data();
    // 校验签名
    RsaCrypto rsa;
    Hash h(T_SHA1);
    h.addData(msg->data());
    bool b1 = rsa.rasVerify(h.result(),msg->sign());
    if(!b1){
        info.rv = false;
        cout << "签名校验失败" << endl;
    }
    else {
        string randStr = getRandStr(16);
        string secStr = rsa.rsaPubKeyEncrypt(randStr);
        info.clientID = msg->clientid();
        info.serverID = m_serverID;
        info.seckeyid = 1;
        info.rv = true;
    }
    CodecFaCctory* factory = new ResponseFactory(&info);
    Codec* c = factory->createCodec();
    string data = c->encodeMsg();
    return data;
}

ServerOp::~ServerOp() {

}

string ServerOp::getRandStr(int num) {
    srand(time(NULL));	// 以当前时间为种子
    string retStr = string();
    char* buf = "~`@#$%^&*()_+=-{}[];':";
    for (int i = 0; i < num; ++i)
    {
        int flag = rand() % 4;
        switch (flag)
        {
            case 0:	// 0-9
                retStr.append(1, rand() % 10 + '0');
                break;
            case 1:	// a-z
                retStr.append(1, rand() % 26 + 'a');
                break;
            case 2:	// A-Z
                retStr.append(1, rand() % 26 + 'A');
                break;
            case 3:	// 特殊字符
                retStr.append(1, buf[rand() % strlen(buf)]);
                break;
        }
    }
    return retStr;
}
