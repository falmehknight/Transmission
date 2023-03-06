#pragma once
#include <iostream>
#include "CodecFaCctory.h"
#include "RequestCodec.h"
using namespace std;
class RequestFactory : public CodecFaCctory
{
public:
	RequestFactory(const string& enc);
	RequestFactory( RequestInfo* info);
	Codec* createCode();
	~RequestFactory();
private:
	bool m_flag;
	string m_encStr;
	RequestInfo* m_info;

};

