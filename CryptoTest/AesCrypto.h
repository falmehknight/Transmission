//
// Created by flame on 23-3-9.
//

#ifndef CRYPTOTEST_AESCRYPTO_H
#define CRYPTOTEST_AESCRYPTO_H

#include<string>
#include<openssl/aes.h>
using namespace std;

class AesCrypto {
public:

    explicit AesCrypto(string key);
    ~AesCrypto();
    /*!
     *
     * @param text
     * @return
     */
    string aesCBCEncrypt(string text);
    /*!
     *
     * @param encStr
     * @return
     */
    string aesCBCDecrypt(string encStr);
private:
    string aesCrypto(string data, int crypto);
    /*!
     * 生成初始化向量给CBC加密方式用
     * @param ivec
     */
    void generateIvec(unsigned char* ivec);
private:
    AES_KEY m_encKey;
    AES_KEY m_decKey;
    string m_key;
};


#endif //CRYPTOTEST_AESCRYPTO_H
