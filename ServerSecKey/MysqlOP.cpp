//
// Created by flame on 23-3-14.
//

#include "MysqlOP.h"

MysqlOP::MysqlOP() {
    m_driver = mysql::get_mysql_driver_instance();
}

MysqlOP::~MysqlOP() {
    delete m_state;
    delete m_conn;
    delete m_driver;
}

bool MysqlOP::connectDB(string connStr, string user, string passwd,string dataBase) {
    m_conn = m_driver->connect(connStr,user,passwd);
    if(m_conn = nullptr) return false;
    cout<<"数据库连接成功"<<endl;
    m_state = m_conn->createStatement();
    m_state->execute("use "+ dataBase);
}

int MysqlOP::getKeyID() {
    string sql = "select ikeysn from keysn";
    ResultSet* resultSet = m_state->executeQuery(sql);
    int keyID = -1;
    if(resultSet->next()){
        keyID = resultSet->getInt(1);
    }
    delete[] resultSet;
    return keyID;
}

bool MysqlOP::updateKeyID(int keyID) {
    string sql = "update keysn set ikeysn = "+ to_string(keyID);
    int ret = m_state->executeUpdate(sql);
    if(ret <= 0) return false;
    else return true;
}

bool MysqlOP::writeSecKey(NodeSecKeyInfo *pNode) {
    char sql[1024] = {0};
    sprintf(sql, "insert into seckeyinfo values('%s','%s',%d,date_format('%s','%%Y%%m%%d%%H%%i%%s'),"
                       "%d,'%s')", pNode->clientID, pNode->serverID, pNode->secKeyID, getCurTime().data(),
                       pNode->status, pNode->secKey);
    cout<<"insert sql:"<<sql<<endl;
    return !(0==m_state->executeUpdate(sql));
}



string MysqlOP::getCurTime() {
    time_t t ;
    time(&t);
    char ch[64] = {0};
    strftime(ch,sizeof(ch)-1,"%Y-%m-%d %H:%M:%S", localtime(&t));
    return string(ch);
}
