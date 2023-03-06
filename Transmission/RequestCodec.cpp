#include "RequestCodec.h"

RequestCodec::RequestCodec()
{
}

RequestCodec::RequestCodec(std::string encstr)
{
    initMessage(encstr);
}



RequestCodec::RequestCodec(RequestInfo* info)
{
    initMessage(info);
}
/// @brief 
/// @param encstr 
void RequestCodec::initMessage(string encstr)
{
    this->m_encStr = encstr;
}

void RequestCodec::initMessage(RequestInfo* info)
{
    this->m_msg.set_cmdtype(info->cmd);
    this->m_msg.set_clientid(info->clientID);
    this->m_msg.set_serverid(info->serverID);
    this->m_msg.set_sign(info->sign);
    this->m_msg.set_data(info->data);
}



string RequestCodec::encodeMsg()
{
    string output;
    this->m_msg.SerializeToString(&output);
    return output;
}

void* RequestCodec::decodeMsg()
{
    this->m_msg.ParseFromString(this->m_encStr);
    return &m_msg;
}

RequestCodec::~RequestCodec()
{
}
