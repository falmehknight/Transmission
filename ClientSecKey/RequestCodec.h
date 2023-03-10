#pragma once
#include <iostream>
#include "Message.pb.h"
#include "Codec.h"

using namespace std;

enum Choice{
    KEY_AGREE,
    KEY_CHECK,
    KEY_LOGOUT
};
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
	//�ն���
	RequestCodec();
	// ������������ڽ���
	RequestCodec(std::string encstr);
	// ������������ڱ���
	RequestCodec(RequestInfo* info);
	//init���ն���ʹ�õ�
	void initMessage(string encstr);
	void initMessage(RequestInfo* info);
	//��д�ĸ��ຯ��->���л��������������л����ַ���
	string encodeMsg();
	// ��д�ĸ��ຯ��->�����л����������ؽṹ��/�����
	void* decodeMsg();
	~RequestCodec();
private:
	//����Ҫ������ַ���
	string m_encStr;
	// ����Ҫ����Ķ���
	RequestMsg m_msg;
};

