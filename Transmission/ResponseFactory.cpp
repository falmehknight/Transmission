#include "ResponseFactory.h"


ResponseFactory::ResponseFactory(const string& enc)
{
    this->m_encStr = enc;
    this->m_flag = true;
    this->m_info = NULL;
   
}

ResponseFactory::ResponseFactory(ResponseInfo* info)
{
    this->m_info = info;
    this->m_flag = false;
    this->m_encStr = "";
}

Codec* ResponseFactory::createCode()
{
    if (this->m_flag) {
        return new ResponseCodec(this->m_encStr);
    }
    else {
        return new ResponseCodec(this->m_info);
    }
}

ResponseFactory::~ResponseFactory()
{
}
