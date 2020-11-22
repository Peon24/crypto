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

   WINAPI::VirtualLock(beginMemory,size); //протестировать

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



//bool MemoryManager::rezerveMemory(uint8_t *beginMemory,SIZE_T size, QString pageType){


//    DWORD pageProtect;

//    if(pageType == "READONLY"){
//        pageProtect = PAGE_READONLY;
//    } else {
//        pageProtect = PAGE_READWRITE;
//    }


//    if( WINAPI::VirtualAlloc(beginMemory,size,MEM_RESERVE,pageProtect)){
//        return true;

//    }

//    return false;

//}


//MemoryManager& MemoryManager::getInstance()
//{

//        static MemoryManager memoryManager;

//        return memoryManager;

//}



