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

    string encode = "";
    int ret = RSA_public_encrypt(data.size(), reinterpret_cast<const unsigned char *>(data.data()),
                                 (unsigned char *) encode.data(), m_publicKey, RSA_PKCS1_PADDING);
    if(ret<0) return string();
    return encode;
}

string RsaCrypto::rsaPriKeyDecrypt(string encData) {

    string deCode = "";
    int ret = RSA_public_encrypt(encData.size(), reinterpret_cast<const unsigned char *>(encData.data()),
                                 (unsigned char *) deCode.data(), m_privateKey, RSA_PKCS1_PADDING);
    if(ret<0) return string();
    return deCode;
}

string RsaCrypto::rsaSign(string data, SignLevel level) {
    string signData="";
    unsigned int len;
    RSA_sign(level, reinterpret_cast<const unsigned char *>(data.data()), data.size(),
             (unsigned char *) signData.data(), &len, m_privateKey);
    return signData;
}

bool RsaCrypto::rasVerify(string data, string signData, SignLevel level) {
    int ret = RSA_verify(level, (const unsigned char*)data.data(), data.size(),
                         (const unsigned char*)signData.data(), signData.size(), m_publicKey);
    if(ret!=1) return false;
    else return true;
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

RSA *RsaCrypto::getMPublicKey() const {
    return m_publicKey;
}

RSA *RsaCrypto::getMPrivateKey() const {
    return m_privateKey;
}
