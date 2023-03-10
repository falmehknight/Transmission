#pragma once
#include <string>
#include "Codec.h"
#include "Message.pb.h"
struct ResponseInfo {
	bool rv;
	int seckeyid;
	std::string clientID;
	std::string serverID;
	std::string data;
};


class ResponseCodec final : public Codec {
public:
	ResponseCodec();
	ResponseCodec(const std::string& encstr);
	ResponseCodec(const ResponseInfo* info);
	void initMessage(const std::string& encstr);
	void initMessage(const ResponseInfo* info);
	virtual std::string encodeMsg() override;
	virtual void* decodeMsg() override;
	ResponseCodec(const ResponseCodec& c) = delete;
	ResponseCodec operator=(const ResponseCodec& c) = delete;
	~ResponseCodec();

private:
	std::string m_encstr;
	RespondMsg m_msg;
};
