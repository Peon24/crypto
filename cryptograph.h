#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <QString>
#include "aes.h"
#include <cmath>

#include <QFile>
#include <QByteArray>
#include <QDir>


class Cryptograph
{
public:
    Cryptograph();


    void encryptFileAES(QByteArray& input , QByteArray& output ,  bool isNewFile = false );
    void decryptFileAES(QByteArray& input , QByteArray& output ,  bool isNewFile = false);
    void setKey(QString key);
    QString keyGen();



private:
   AES aes;
  // uint8_t key[16];
   QString path;


};

#endif // ENCRYPT_H
