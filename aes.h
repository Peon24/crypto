#ifndef AES_H
#define AES_H
#include <string>
#include <cstring>
//#include <algorithm>
#include <iostream>
#include <QString>

class AES
{
public:
    AES();

    void encrypt( uint8_t state[4][4], uint8_t key[], uint8_t output[]) ;
    int checkKey(QString key);
private:

  static constexpr int EXPANDED_KEY_LENGTH = 176;
  static constexpr int INITIAL_KEY_LENGTH = 16;


     uint8_t state[4][4];

     void SubBytes (uint8_t state[4][4]);
     void SubBytes (uint8_t keyColumn[4]);

      void SubBytes (uint8_t* keyColumn[]);

     void ShiftRows(uint8_t state[4][4]);
     void MixColumn(uint8_t state[4][4]);
     void AddRoundKey(uint8_t state[4][4],uint8_t roundKey[4][4]);

     void KeyExpansion( const uint8_t key[] , uint8_t wKey[]);
     //void KeyShedule(uint8_t )
};

#endif // AES_H
