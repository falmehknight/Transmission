#pragma once
#include<iostream>
#include"CodecFaCctory.h"
#include"ResponseCodec.h"
using namespace std;
class ResponseFactory : public CodecFaCctory
{
public:
	ResponseFactory(const string& enc);
	ResponseFactory(ResponseInfo* info);
	Codec* createCode();
	~ResponseFactory();
private:
	bool m_flag;
	string m_encStr;
	ResponseInfo* m_info;
};

