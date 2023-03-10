#include "ResponseFactory.h"


ResponseFactory::ResponseFactory(const string& enc)
{
    this->m_encStr = enc;
    this->m_flag = true;
   
}

ResponseFactory::ResponseFactory(ResponseInfo* info)
{
    this->m_info = info;
    this->m_flag = false;
}

Codec* ResponseFactory::createCodec()
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
