#ifndef AES_H
#define AES_H
#include <string>
#include <iostream>
#include <QString>
#include <random>
#include <ctime>
#include "memorymanager.h"

constexpr uint8_t blockSize = 16;

class AES
{

public:

    explicit AES();

    ~AES() = default;

    void newFile(uint8_t IV[16],bool encrypt);
    void encrypt(uint8_t state[4][4],  uint8_t output[]);
    void decrypt( uint8_t state[4][4],  uint8_t output[]);

    bool setKey(QByteArray &key);

    static int checkKey( const QString &key);
    static QString generateKey();

    void convertAndSetIV(QByteArray &IV);

    void  getPointersToLock(QMap<uint8_t*,size_t>& ptrsForLock);


    static constexpr int EXPANDED_KEY_LENGTH = 176;
    static constexpr int INITIAL_KEY_LENGTH = 16;

private:

    QMap<uint8_t*,size_t> m_ptrsForLock; //все что может выдать ключ

    bool convertToKeyUInt8(QByteArray &input);

    static constexpr int ROUND_MAX = 10;

    uint8_t m_key[INITIAL_KEY_LENGTH] ;
    uint8_t m_wKey[EXPANDED_KEY_LENGTH];
    uint8_t m_prevState[4][4];
    uint8_t m_roundKey[4][4];


    uint8_t buffer[4][4];


    void generateInitialVec();
    void StateXorPrevState(uint8_t state[4][4]);

    void KeyExpansion() ;
    void AddRoundKey(uint8_t state[4][4],uint8_t roundKey[4][4]);

    //методы шифрования
    void SubBytes (uint8_t state[4][4]);
    void SubBytes (uint8_t keyColumn[4]);
    void ShiftRows(uint8_t state[4][4]);
    void MixColumn(uint8_t state[4][4]);


    //метода дешифрования
    void invSubBytes (uint8_t state[4][4]);
    void invSubBytes (uint8_t keyColumn[4]);
    void invShiftRows(uint8_t state[4][4]);
    void invMixColumn(uint8_t state[4][4]);


};

#endif // AES_H
