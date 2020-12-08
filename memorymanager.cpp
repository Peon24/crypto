#include "memorymanager.h"

MemoryManager::MemoryManager()
{

}

MemoryManager::~MemoryManager()
{

 clearAll();

}


QMap<uint8_t*,size_t>& MemoryManager::getLockPtrs(){

    return m_lockPtrs;
}


void MemoryManager::lockMemory(uint8_t *beginMemory, SIZE_T size){

   WINAPI::VirtualLock(beginMemory,size);

   m_lockPtrs.insert(beginMemory,size);

}


void MemoryManager::lockAll() {

    QMap<uint8_t*, size_t>::const_iterator it = m_lockPtrs.constBegin();

    while (it != m_lockPtrs.constEnd()) {

     uint8_t* beginMemory = it.key();
     size_t sizeBlock = it.value() ;

     lockMemory(beginMemory,sizeBlock);

     ++it;

    }

}


void MemoryManager::clearAll(){

    QMap<uint8_t*, size_t>::const_iterator it = m_lockPtrs.constBegin();

    while (it != m_lockPtrs.constEnd()) {

     uint8_t* beginMemory = it.key();
     size_t sizeBlock = it.value() ;

     WINAPI::SecureZeroMemory(beginMemory,sizeBlock);

     ++it;

    }

}






