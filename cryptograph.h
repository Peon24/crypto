#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <QString>
#include "aes.h"
#include "memorymanager.h"
#include <cmath>
#include "filemanager.h"
#include <memory>
#include <QFile>
#include <QByteArray>
#include <QDir>
#include "filemanager.h"






class Cryptograph
{
public:
   explicit Cryptograph( QByteArray &key ,QByteArray &IV,QString encryptionType = "AES");
    Cryptograph() = delete;


    int start(QString path,  bool encrypt ,  size_t sizeFile  ,bool needIV = true );

    QString keyGen();
    static int checkKey( const QString &key );

    Cryptograph(const Cryptograph&) = delete;
    Cryptograph& operator=(const Cryptograph&) = delete;
    ~Cryptograph() ;


private:
    void encryptFileAES(QByteArray& input,QByteArray& output ,bool isNewFile = false);
    void decryptFileAES(QByteArray& input,QByteArray& output ,bool isNewFile = false);
    void writeNeedDelete(QByteArray& input ,const size_t size);

   AES aes;

   MemoryManager memoryManager;
   QString path;

};

#endif // ENCRYPT_H
