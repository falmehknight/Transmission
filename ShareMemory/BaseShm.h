//
// Created by flame on 23-3-8.
//

#ifndef SHAREMEMORY_BASESHM_H
#define SHAREMEMORY_BASESHM_H
#include <iostream>;
using namespace std;

class BaseShm {
public:
    /*!
     *  通过key打开共享内存
     * @param key
     */
    BaseShm(int key);
    /*!
     * 通过传递来的key和size创建/打开共享内存
     * @param key
     * @param size
     */
    BaseShm(int key, int size);
    /*!
     *通过路径转换为key然后打开共享内存
     * @param name
     */
    BaseShm(string name);
    /*!
     *通过路径和key创建/打开共享内存
     * @param name
     * @param size
     */
    BaseShm(string name,int size);
    /*!
     *  进程和共享内存产生联系
     * @return 返回的是共享内存的起始地址
     */
    void* mapShm();
    /*!
     *  解除与共享内存联系
     * @return 成功返回0，失败返回-1
     */
    int unmapShm();
    /*!
     *  标记要删除共享内存
     * @return 成功返回0，失败返回-1
     */
    int delShm();
    /*!
     *
     */
    ~BaseShm();
private:
    /*!
     *内部调用的创建共享内存的函数
     * @param key
     * @param shmSize
     * @param flag
     * @return
     */
    int getShmID(key_t key,int shmSize,int flag);

private:
    int m_shmID;
protected:
    void* m_shmAddr; //共享内存的起始地址
};


#endif //SHAREMEMORY_BASESHM_H
