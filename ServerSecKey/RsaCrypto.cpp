//
// Created by flame on 23-3-8.
//

#include "RsaCrypto.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <iostream>
#include <openssl/buffer.h>

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
    cout << "加密数据长度: " << data.size() << endl;
    // 计算公钥长度
    int keyLen = RSA_size(m_publicKey);
    cout << "pubKey len: " << keyLen << endl;
    // 申请内存空间
    char* encode = new char[keyLen + 1];
    // 使用公钥加密
    int ret = RSA_public_encrypt(data.size(), (const unsigned char*)data.data(),
                                 (unsigned char*)encode, m_publicKey, RSA_PKCS1_OAEP_PADDING);
    string retStr = string();
    if (ret >= 0)
    {
        // 加密成功
        cout << "ret: " << ret << ", keyLen: " << keyLen << endl;
        retStr = toBase64(encode, ret);
    }
    else
    {
        ERR_print_errors_fp(stdout);
    }
    // 释放资源
    delete[]encode;
    return retStr;
}

string RsaCrypto::rsaPriKeyDecrypt(string encData) {

    char* text = fromBase64(encData);
    int keyLen = RSA_size(m_privateKey);
    char* decode = new char[keyLen+1];
    int ret = RSA_private_decrypt(keyLen, (const unsigned char *)(text),
                                 (unsigned char *) decode, m_privateKey, RSA_PKCS1_OAEP_PADDING);
    string retSrc = string();
    if(ret>=0) {
        retSrc = string(decode,ret);
    }
    else {
        cout << "私钥解密失败..." << endl;
        ERR_print_errors_fp(stdout);
    }

    delete[] decode;
    delete[] text;
    return retSrc;
}

string RsaCrypto::rsaSign(string data, SignLevel level) {
    //直接用string 是不行的
    char* signBuf = new char[1024];
    memset(signBuf,0,1024);
    unsigned int len;
    int ret = RSA_sign(level, reinterpret_cast<const unsigned char *>(data.data()), data.size(),
             (unsigned char *) signBuf, &len, m_privateKey);
    if(ret == -1){
        ERR_print_errors_fp(stdout);
    }
    cout<< "sign len:"<< len << ",ret:" << ret <<endl;
    string retStr = toBase64(signBuf,len);
    delete[] signBuf;
    return retStr;
}

bool RsaCrypto::rasVerify(string data, string signData, SignLevel level) {
    int keyLen = RSA_size(m_publicKey);
    char* sign = fromBase64(signData);
    int ret = RSA_verify(level, (const unsigned char*)data.data(), data.size(),
                         (const unsigned char*)sign, keyLen, m_publicKey);
    delete[] sign;
    if(ret == -1) {
        ERR_print_errors_fp(stdout);
    }
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

bool RsaCrypto::initPrivateKey(string priFile) {
    // 通过BIO读文件
    BIO* priBio = BIO_new_file(priFile.data(), "r");
    // 将bio中的pem数据读出
    if (PEM_read_bio_RSAPrivateKey(priBio, &m_privateKey, NULL, NULL) == NULL)
    {
        ERR_print_errors_fp(stdout);
        return false;
    }
    BIO_free(priBio);
    return true;
}

RSA *RsaCrypto::getMPublicKey() const {
    return m_publicKey;
}

RSA *RsaCrypto::getMPrivateKey() const {
    return m_privateKey;
}

string RsaCrypto::toBase64(const char *str, int len) {
    BIO* mem = BIO_new(BIO_s_mem());
    BIO* bs64 = BIO_new(BIO_f_base64());
    // mem添加到bs64中
    bs64 = BIO_push(bs64, mem);
    // 写数据
    BIO_write(bs64, str, len);
    BIO_flush(bs64);
    // 得到内存对象指针
    BUF_MEM *memPtr;
    BIO_get_mem_ptr(bs64, &memPtr);
    string retStr = string(memPtr->data, memPtr->length - 1);
    BIO_free_all(bs64);
    return retStr;
}

char* RsaCrypto::fromBase64(string str) {
    int length = str.size();
    BIO* bs64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new_mem_buf(str.data(), length);
    BIO_push(bs64, mem);
    char* buffer = new char[length];
    memset(buffer, 0, length);
    BIO_read(bs64, buffer, length);
    BIO_free_all(bs64);

    return buffer;
}

void RsaCrypto::parseKeyString(string keyStr, bool pubkey) {
    BIO* bio = BIO_new_mem_buf(keyStr.data(),keyStr.size());

    if(pubkey){
        PEM_read_bio_RSAPublicKey(bio,&m_publicKey, nullptr, nullptr);
    }
    else {
        PEM_read_bio_RSAPrivateKey(bio,&m_privateKey, nullptr,nullptr);
    }
    BIO_free(bio);
}
