//
// Created by flame on 23-3-8.
//

#ifndef CRYPTOTEST_HASH_H
#define CRYPTOTEST_HASH_H

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <iostream>
#include <string.h>
using namespace std;

enum HashType{
    T_MD5,
    T_SHA1,
    T_SHA224,
    T_SHA256,
    T_SHA384,
    T_SHA512
};
class Hash {
public:
    /*!
     * 初始化
     * @param type 标识所用的hash函数
     */
    Hash(HashType type);
    ~Hash();
    /*!
     *  将数据进行hash
     * @param data 需要进行hash运算的数据
     */
    void addData(string data);
    /*!
     *
     * @return 返回hash的结果（以16进制显示）
     */
    string result();
private:
    //md5
    inline void md5Init(){
        MD5_Init(&m_md5);
    }
    inline void md5AddData(const char * data){
        MD5_Update(&m_md5,data,strlen(data));
    }
    string md5Result();


    // sha1
    inline void sha1Init() { SHA1_Init(&m_sha1); }
    inline void sha1AddData(const char* data)
    {
        SHA1_Update(&m_sha1, data, strlen(data));
    }
    string sha1Result();

    // sha224
    inline void sha224Init() { SHA224_Init(&m_sha224); }
    inline void sha224AddData(const char* data)
    {
        SHA224_Update(&m_sha224, data, strlen(data));
    }
    string sha224Result();

    // sha256
    inline void sha256Init() { SHA256_Init(&m_sha256); }
    inline void sha256AddData(const char* data)
    {
        SHA256_Update(&m_sha256, data, strlen(data));
    }
    string sha256Result();

    // sha384
    inline void sha384Init() { SHA384_Init(&m_sha384); }
    inline void sha384AddData(const char* data)
    {
        SHA384_Update(&m_sha384, data, strlen(data));
    }
    string sha384Result();

    // sha512
    inline void sha512Init() { SHA512_Init(&m_sha512); }
    inline void sha512AddData(const char* data)
    {
        SHA512_Update(&m_sha512, data, strlen(data));
    }
    string sha512Result();
private:
    HashType m_type;
    MD5_CTX m_md5;
    SHA_CTX m_sha1;
    SHA256_CTX m_sha224;
    SHA256_CTX m_sha256;
    SHA512_CTX m_sha384;
    SHA512_CTX m_sha512;
};


#endif //CRYPTOTEST_HASH_H
