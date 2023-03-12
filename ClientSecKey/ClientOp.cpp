//
// Created by flame on 23-3-10.
//

#include "ClientOp.h"
#include <iostream>
#include <fstream>
#include <json/json.h>
#include "RsaCrypto.h"
#include "RequestCodec.h"
#include "RequestFactory.h"
#include "ResponseFactory.h"
#include "ResponseCodec.h"
#include "Hash.h"
#include "TcpSocket.h"
#include <string>
using namespace Json;

ClientOp::ClientOp(string jsonFile) {
    cout<< "正在读取配置文件"<<endl;
    ifstream ifs(jsonFile);
    Reader r;
    Value root;
    r.parse(ifs,root);
    ifs.close();
    m_info.serverID = root["ServerID"].asString();
    m_info.clientID = root["ClientID"].asString();
    m_info.ip = root["ServerIP"].asString();
    m_info.port = root["Port"].asInt();
    cout<<"ServerID"<<m_info.serverID<<",ClientID:"<<m_info.clientID<<endl;

}

bool ClientOp::secKeyAgree() {
    // 生成密钥对
    RsaCrypto rsa;
    rsa.generateRsaKey(1024);
    // rsa.getMPublicKey()
    // 读公钥文件
    ifstream ifs("public.pem");
    stringstream str;
    str << ifs.rdbuf();
    // 初始化序列化数据
    // 序列化的类对象-》工厂类创建
    RequestInfo reqInfo;
    reqInfo.clientID = m_info.clientID;
    reqInfo.serverID = m_info.serverID;
    reqInfo.cmd = KEY_AGREE;  //密钥协商
    reqInfo.data = str.str();  //非对称加密的公钥
    cout<<"数据完成"<<endl;    // hash运算
    Hash a(T_SHA1);
    a.addData(str.str());
    reqInfo.sign = rsa.rsaSign(a.result()); //公钥的签名
    cout<<"签名完成"<<endl;
    CodecFaCctory* factory = new RequestFactory(&reqInfo);
    Codec* c = factory->createCodec();
    //得到序列之后的数据，可以将其发送给服务器端
    string encStr = c->encodeMsg();
    cout<<"数据序列化之后，准备发给服务器,长度为:"<<encStr.size()<<endl;
    //释放资源
    delete factory;
    delete c;

    //套接字通信
    TcpSocket* tcp = new TcpSocket;
    int ret;
    ret = tcp->connectToHost(m_info.ip,m_info.port);
    cout<<"ip:"<<m_info.ip<<",port"<<m_info.port<<endl;
    if(ret != 0){
        cout << "连接服务器失败..." << endl;
        return false;
    }
    cout << "连接服务器成功..." << endl;
    //发送序列化数据
   tcp->sendMsg(encStr);

    //等待服务器回复
    string msg = tcp->recMsg();

    // 解析服务器数据 -> 解码
    factory = new ResponseFactory(msg);
    c = factory->createCodec();
    RespondMsg* resData = static_cast<RespondMsg *>(c->decodeMsg());
    // 判断状态
    if(!resData->rv()){
        cout << "密钥协商失败" << endl;
        return false;
    }
    //将得到的密文解密
    string key = rsa.rsaPriKeyDecrypt(resData->data());
    cout << "对称加密的密钥：" << key << endl;

    delete factory;
    delete c;
    delete tcp;

    return true;
}

bool ClientOp::secKeyCheck() {
    return false;
}

bool ClientOp::secKeyLogout() {
    return false;
}

ClientOp::~ClientOp() {

}
