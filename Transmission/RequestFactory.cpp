#include "RequestFactory.h"

RequestFactory::RequestFactory(const string& enc)
{
    this->m_encStr = enc;
    this->m_flag = true;
}

RequestFactory::RequestFactory( RequestInfo* info)
{
    this->m_info = info;
    this->m_flag = false;
}

Codec* RequestFactory::createCode()
{
    if (this->m_flag == true) {
        return new RequestCodec(m_encStr);
    }
    else {
        return new RequestCodec(m_info);
    }
}

RequestFactory::~RequestFactory()
{
}
