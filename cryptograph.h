#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <QString>
#include "aes.h"
#include <cmath>

class Encrypt : public AES
{
public:
    Encrypt();


    void encryptFile(QByteArray& input , QByteArray& output  );
    void setKey(QByteArray key);



private:
   bool checkKey( const QByteArray&  key );
   uint8_t key[16];
   QString path;

};

#endif // ENCRYPT_H
