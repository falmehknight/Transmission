//
// Created by flame on 23-3-8.
//

#ifndef CRYPTOTEST_RSACRYPTO_H
#define CRYPTOTEST_RSACRYPTO_H
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
using namespace std;

enum SignLevel{
    level1 = NID_md5,
    Level2 = NID_sha1,
    Level3 = NID_sha224,
    Level4 = NID_sha256,
    Level5 = NID_sha384,
    Level6 = NID_sha512
};
class RsaCrypto {
public:
    RsaCrypto();
    /*!
     * 根据已存在的直接读密钥
     * @param filename
     * @param isPrivate
     */
    explicit RsaCrypto(string filename,bool isPrivate = true);
    ~RsaCrypto();
    /*!
     *  得到公钥和私钥
     * @param bits 密钥的长度，为n*1024
     * @param pub 公钥文件名
     * @param pri 私钥文件名
     */
    void generateRsaKey(int bits,string pub = "public.pem",string pri = "private.pem");
    /*!
     * 公钥加密
     * @param data 要加密的数据
     * @return 加密之后的密文
     */
    string rsaPubKeyEncrypt(string data);
    /*!
     * 私钥解密
     * @param encData  要解密的数据
     * @return 解密之后的明文
     */
    string rsaPriKeyDecrypt(string encData);
    /*!
     * 数字签名
     * @param data 数据
     * @param level 使用的hash函数
     * @return 处理之后的数据
     */
    string rsaSign(string data,SignLevel level=Level3);
   /*!
    * 验证数字签名
    * @param data 原数据
    * @param signData 签名数据
    * @param level hash函数
    * @return 返回验证是否符合
    */
    bool rasVerify(string data, string signData,SignLevel level = Level3);

    RSA *getMPublicKey() const;

    RSA *getMPrivateKey() const;
    /*!
     * 将公钥/私钥字符串数据解析到RSA对象中
     * @param keyStr 公钥/私钥的字符串
     * @param pubkey 是否是公钥
     */
    void parseKeyString(string keyStr, bool pubkey=true);

private:
    /*!
     * 根据文件名(文件位置)读公钥
     * @param pubFile
     * @return
     */
    bool initPublicKey(string pubFile);
    /*!
     * 根据文件名（位置）读私钥
     * @param pubFile
     * @return
     */
    bool initPrivateKey(string priFile);
    /*!
     * base64编码，将要传输的二进制数据转换为base64编码
     * @param str 要传输的二进制数据
     * @param len 长度
     * @return
     */
    string toBase64(const char* str, int len);
    /*!
     * 将base64编码的数据还原
     * @param str 编码的数据
     * @return 还原之后的数据
     */
    char* fromBase64(string str);
private:
    RSA* m_publicKey; //公钥
    RSA* m_privateKey; //私钥
};


#endif //CRYPTOTEST_RSACRYPTO_H
