#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <QString>
#include "aes.h"
#include "memorymanager.h"
#include <cmath>


#include <QFile>
#include <QByteArray>
#include <QDir>



class Cryptograph
{
public:
    explicit Cryptograph( QByteArray &key , QByteArray &IV,QString encryptionType = "AES");
    Cryptograph() = delete;
   ~Cryptograph();

    void encryptFileAES(QByteArray& input,QByteArray& output ,bool isNewFile = false);
    void decryptFileAES(QByteArray& input,QByteArray& output ,bool isNewFile = false);

    QString keyGen();


private:
   AES *aes;
   MemoryManager *memoryManager;
   QString path;

};

#endif // ENCRYPT_H
