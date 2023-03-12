#include "ResponseCodec.h"
//Ĭ�Ϲ��죬�ֶ�����initMessage()
ResponseCodec::ResponseCodec() {
}

//���ڷ����л�
ResponseCodec::ResponseCodec(const std::string encstr) {
	initMessage(encstr);
}

//�������л�
ResponseCodec::ResponseCodec(const ResponseInfo* info) {
	initMessage(info);
}

//���ڷ����л�
void ResponseCodec::initMessage(const std::string encstr) {
	this->m_encstr = encstr;
}

//�������л�
void ResponseCodec::initMessage(const ResponseInfo* info) {
	this->m_msg.set_seckeyid(info->seckeyid);
	this->m_msg.set_clientid(info->clientID);
	this->m_msg.set_serverid(info->serverID);
	this->m_msg.set_data(info->data);
	this->m_msg.set_rv(info->rv);
}

//��m_msg�е���Ϣ���л�Ϊstring������
std::string ResponseCodec::encodeMsg() {
	std::string output;
	this->m_msg.SerializeToString(&output);
	return output;
}

//��m_encstr�е���Ϣ�����л�ΪResponseInfo��������ָ��
void* ResponseCodec::decodeMsg() {
	this->m_msg.ParseFromString(this->m_encstr);

	return &(this->m_msg);
}

ResponseCodec::~ResponseCodec() {
}