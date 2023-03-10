//
// Created by flame on 23-3-10.
//

#include <fstream>
#include <json/json.h>
#include "ServerOp.h"
using namespace Json;

ServerOp::ServerOp(string json) {
    ifstream ifs(json);
    Reader reader;
    Value root;
    reader.parse(ifs,root);

    m_serverID = root["ServerID"].asString();
    m_port = root["Port"].asInt();
}

void ServerOp::startServer() {

}

void *ServerOp::working(void *arg) {
    return nullptr;
}

string ServerOp::secKeyAgree(RequestMsg *msg) {
    return std::string();
}

ServerOp::~ServerOp() {

}

string ServerOp::getRandStr(int num) {
    return std::string();
}
