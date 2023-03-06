#include "ResponseCodec.h"
//默认构造，手动调用initMessage()
ResponseCodec::ResponseCodec() {
}

//用于反序列化
ResponseCodec::ResponseCodec(const std::string& encstr) {
	initMessage(encstr);
}

//用于序列化
ResponseCodec::ResponseCodec(const ResponseInfo* info) {
	initMessage(info);
}

//用于反序列化
void ResponseCodec::initMessage(const std::string& encstr) {
	this->m_encstr = encstr;
}

//用于序列化
void ResponseCodec::initMessage(const ResponseInfo* info) {
	this->m_msg.set_seckeyid(info->seckeyid);
	this->m_msg.set_clientid(info->clientID);
	this->m_msg.set_serverid(info->serverID);
	this->m_msg.set_data(info->data);
	this->m_msg.set_rv(info->rv);
}

//将m_msg中的信息序列化为string并返回
std::string ResponseCodec::encodeMsg() {
	std::string output;
	this->m_msg.SerializeToString(&output);
	return output;
}

//将m_encstr中的信息反序列化为ResponseInfo并返回其指针
void* ResponseCodec::decodeMsg() {
	this->m_msg.ParseFromString(this->m_encstr);

	return &(this->m_msg);
}

ResponseCodec::~ResponseCodec() {
}