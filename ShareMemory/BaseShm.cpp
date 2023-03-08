//
// Created by flame on 23-3-8.
//

#include "BaseShm.h"
#include <sys/ipc.h>
#include <sys/shm.h>

const char RandA = 'a';

BaseShm::BaseShm(int key) {
    getShmID(key,0,0);
}

BaseShm::BaseShm(int key, int size) {
   getShmID(key,size,IPC_CREAT | 0664);
}

BaseShm::BaseShm(string name) {
    key_t key = ftok(name.data(),RandA);
    getShmID(key,0,0);
}

BaseShm::BaseShm(string name, int size) {
    key_t key = ftok(name.data(),RandA);
    getShmID(key,size,IPC_CREAT | 0664);
}

void *BaseShm::mapShm() {
    this->m_shmAddr = shmat(this->m_shmID, nullptr,0);
    if(m_shmAddr == (void*)-1){
        return nullptr
    }
    return m_shmAddr;
}

int BaseShm::unmapShm() {
    int ret = shmdt(m_shmAddr);
    return ret;
}

int BaseShm::delShm() {
    int ret = shmctl(m_shmID,IPC_RMID, nullptr);
    return ret;
}

BaseShm::~BaseShm() {

}

int BaseShm::getShmID(key_t key, int shmSize, int flag) {
    cout << "share memory size: "<< shmSize <<endl;
    m_shmID = shmget(key,shmSize,flag);
    if(m_shmID == -1){
        cout<< "share memory create 失败"<<endl;
    }
    return m_shmID;
}
