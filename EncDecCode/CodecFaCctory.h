#pragma once
#include "Codec.h"
class CodecFaCctory
{
public:
	
	CodecFaCctory();
	virtual Codec* createCodec() = 0;
	virtual ~CodecFaCctory();

};

