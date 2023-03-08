//
// Created by flame on 23-3-8.
//

#include "RsaCrypto.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <iostream>

RsaCrypto::RsaCrypto() {
    m_publicKey = RSA_new();
    m_privateKey = RSA_new();
}

RsaCrypto::RsaCrypto(string filename, bool isPrivate) {
    m_publicKey = RSA_new();
    m_privateKey = RSA_new();
    if(isPrivate){
        initPrivateKey(filename);
    }
    else {
        initPublicKey(filename);
    }
}

RsaCrypto::~RsaCrypto() {
    RSA_free(m_publicKey);
    RSA_free(m_privateKey);
}

void RsaCrypto::generateRsaKey(int bits, string pub, string pri) {
    RSA* r =RSA_new();
    BIGNUM* e =BN_new();
    //初始化e对象
    BN_set_word(e,12345);
    RSA_generate_key_ex(r,bits,e, nullptr);
    BIO* pubIO = BIO_new_file(pub.data(),"w");
    PEM_write_bio_RSAPublicKey(pubIO,r);
    BIO_flush(pubIO);
    BIO_free(pubIO);

    // 创建bio对象
    BIO* priBio = BIO_new_file(pri.data(), "w");
    // 私钥以pem格式写入文件中
    PEM_write_bio_RSAPrivateKey(priBio, r, NULL, NULL, 0, NULL, NULL);
    BIO_flush(priBio);
    BIO_free(priBio);

    // 得到公钥和私钥
    m_privateKey = RSAPrivateKey_dup(r);
    m_publicKey = RSAPublicKey_dup(r);

    // 释放资源
    BN_free(e);
    RSA_free(r);
}

string RsaCrypto::rsaPubKeyEncrypt(string data) {
    return std::string();
}

string RsaCrypto::rsaPriKeyDecrypt(string encData) {
    return std::string();
}

string RsaCrypto::rsaSign(string data, SignLevel level) {
    return std::string();
}

bool RsaCrypto::rasVerify(string data, string signData, SignLevel level) {
    return false;
}

bool RsaCrypto::initPublicKey(string pubFile) {
    BIO* pubBio = BIO_new_file(pubFile.data(),"r");
    if(PEM_read_bio_RSAPublicKey(pubBio,&m_publicKey, nullptr, nullptr) == nullptr){
        ERR_print_errors_fp(stdout);
        return false;
    }
    BIO_free(pubBio);
    return true;
}

bool RsaCrypto::initPrivateKey(string pubFile) {
    // 通过BIO读文件
    BIO* pubBio = BIO_new_file(pubFile.data(), "r");
    // 将bio中的pem数据读出
    if (PEM_read_bio_RSAPublicKey(pubBio, &m_publicKey, NULL, NULL) == NULL)
    {
        ERR_print_errors_fp(stdout);
        return false;
    }
    BIO_free(pubBio);
    return true;
}
