#pragma once
#include <iostream>
#include "Message.pb.h"
#include "Codec.h"

using namespace std;

struct RequestInfo {
	int cmd;
	string clientID;
	string serverID;
	string sign;
	string data;
};

class RequestCodec :
	public Codec
{
public:
	//空对象
	RequestCodec();
	// 构造出对象用于解码
	RequestCodec(std::string encstr);
	// 构造出对象用于编码
	RequestCodec(RequestInfo* info);
	//init给空对象使用的
	void initMessage(string encstr);
	void initMessage(RequestInfo* info);
	//重写的父类函数->序列化函数，返回序列化的字符串
	string encodeMsg();
	// 重写的父类函数->反序列化函数，返回结构体/类对象
	void* decodeMsg();
	~RequestCodec();
private:
	//保存要解码的字符串
	string m_encStr;
	// 保存要加码的对象
	RequestMsg m_msg;
};

