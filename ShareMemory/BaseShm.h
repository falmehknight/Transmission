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
     *
     * @param key
     */
    BaseShm(int key);
    /*!
     *
     * @param key
     * @param size
     */
    BaseShm(int key, int size);
    /*!
     *
     * @param name
     */
    BaseShm(string name);
    /*!
     *
     * @param name
     * @param size
     */
    BaseShm(string name,int size);
    /*!
     *
     * @return
     */
    void* mapShm();
    /*!
     *
     * @return
     */
    int unmapShm();
    /*!
     *
     * @return
     */
    int delShm();
    /*!
     *
     */
    ~BaseShm();
private:
    /*!
     *
     * @param key
     * @param shmSize
     * @param flag
     * @return
     */
    int getShmID(key_t key,int shmSize,int flag);

private:
    int m_shmID;
    void* m_shmAddr;
};


#endif //SHAREMEMORY_BASESHM_H
