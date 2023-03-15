//
// Created by flame on 23-3-14.
//

#ifndef SERVERSECKEY_MYSQLOP_H
#define SERVERSECKEY_MYSQLOP_H
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <mysql_driver.h>
#include <string.h>
#include <iostream>
#include "SecKeyNodeInfo.h"
using namespace std;
using namespace sql;
class MysqlOP {
public :
    MysqlOP();
    ~MysqlOP();
    /*!
     * 连接数据库
     * @param connStr 数据库的参数地址
     * @param user 用户名
     * @param passwd 密码
     * @param dataBase 要操作的表
     * @return
     */
    bool connectDB(string connStr, string user,string passwd,string dataBase);
    /*!
     * 得到keyID
     * @return
     */
    int getKeyID();
    /*!
     *
     * @param keyID
     * @return
     */
    bool updateKeyID(int keyID);
    /*!
     *
     * @param pNode
     * @return
     */
    bool writeSecKey( NodeSecKeyInfo *pNode);

private:
    string getCurTime();
private:
    Connection* m_conn;
    mysql::MySQL_Driver* m_driver;
    Statement* m_state;




};


#endif //SERVERSECKEY_MYSQLOP_H
