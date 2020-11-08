#ifndef AES_H
#define AES_H
#include <string>
#include <cstring>
#include <sha3.h>
#include <iostream>
#include <QString>
#include <random>
#include <ctime>

constexpr uint8_t blockSize = 16;

class AES
{

public:

    AES();

    void encrypt(uint8_t state[4][4],  uint8_t output[] );
    void decrypt( uint8_t state[4][4],  uint8_t output[]);

    void newFile();

    void setKey(QString key);
    QString generateKey();



private:

    uint8_t inVec[4][4];
    uint8_t PrevState[4][4];
    SHA3 sha3;

    static constexpr int EXPANDED_KEY_LENGTH = 176;
    static constexpr int INITIAL_KEY_LENGTH = 16;
    static constexpr int ROUND_MAX = 10;

    uint8_t key[INITIAL_KEY_LENGTH];
    std::mt19937 gen;

    bool checkKey(uint8_t key[]);

    void generateInitialVec();
    void StateXorPrevState(uint8_t state[4][4]);


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



    void KeyExpansion( const uint8_t key[] , uint8_t wKey[]);
    //void SubBytes (uint8_t* keyColumn[]);
};

#endif // AES_H
