#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <QString>
#include <windows.h>
#include <QMap>




class MemoryManager
{
public:

   explicit  MemoryManager();

    void lockMemory(uint8_t *beginMemory, SIZE_T size);
    void lockAll();

    void clearAll();


    QMap<uint8_t*,size_t>& getLockPtrs();

    ~MemoryManager();



private :

   QMap<uint8_t*,size_t>  m_lockPtrs;

};

#endif
