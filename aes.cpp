#include "aes.h"


 constexpr  uint8_t S_BOX [256] =
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

 constexpr uint8_t blockSize = 16;

AES::AES()
{

}



int AES::checkKey(QString key){



}


void AES::encrypt( uint8_t state[4][4],  uint8_t *key, uint8_t *output)  {


     static constexpr int ROUND_MAX = 10;

     int roundKeyIterator = 0;


//     uint8_t tes = state[2][2];
//     uint8_t tes2 = state[0][1];
//     uint8_t tes23 = state[0][2];
//     uint8_t tes24 = state[0][3];



//     uint8_t tesdf = state[3][3];
//     uint8_t tesd2f = state[1][0];
//     uint8_t tesd1f = state[2][0];
//     uint8_t te1sdf = state[3][0];


//   //разбитый инпут, разбивать до передачи
//    uint8_t state[4][4]=
//    {   {input[0], input[4], input[8], input[12]},
//        {input[1], input[5], input[9], input[13]},
//        {input[2], input[6], input[10], input[14]},
//        {input[3], input[7], input[11], input[15]}  };


    uint8_t wKey[EXPANDED_KEY_LENGTH];

    KeyExpansion(key ,wKey);


    uint8_t roundKey [4][4]=
         {   {wKey[0], wKey[4], wKey[8], wKey[12]},
             {wKey[1], wKey[5], wKey[9], wKey[13]},
             {wKey[2], wKey[6], wKey[10], wKey[14]},
             {wKey[3], wKey[7], wKey[11], wKey[15]}  }; // ошибка? я беру первые элементы ключа ИСПРАВИТЬ



    AddRoundKey(state,roundKey); //INITIAL ROUND



    for(int round = 1 ;round <= ROUND_MAX; round++){  // 9 ROUNDS

        for (uint8_t i = 0; i < 4; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                //брать по 16 байт ??
                roundKey[i][j] = wKey[(round * blockSize) + (j * 4) + i ];
            }
        }

         roundKeyIterator += blockSize;
        SubBytes(state);
        ShiftRows(state);

        if(round != ROUND_MAX){
        MixColumn(state);
        }

        AddRoundKey(state,roundKey);


    }



    for (uint8_t i = 0; i < 4; i++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                output[(j * 4) + i] = state[i][j];
//                uint8_t test = state[i][j];
//                 uint8_t test2 = state[i][j];
            }
        }
}



void AES::KeyExpansion( const uint8_t key[] , uint8_t wKey[]) {

    static constexpr uint8_t null = 0;

    static constexpr uint8_t RCON [11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

    //uint8_t keyIterator = INITIAL_KEY_LENGTH;
    int keyIterator = INITIAL_KEY_LENGTH;

    memset(wKey, 0, EXPANDED_KEY_LENGTH);
    memcpy(wKey, key, INITIAL_KEY_LENGTH);

    for(int i = 0; i < 10; i++){

        //получаем последние 4 байта
        uint8_t lastByte [4];
        memcpy(lastByte, wKey + (keyIterator - 4), 4);

        //замена
        std::swap(lastByte [3] , lastByte[0]);

        //SBOX
        SubBytes(lastByte);

        //XOR c 1 столбцом  AND RCON
        for(int column = 0; column < 4; column++){


            for(int j=0;j<4;j++){

               if (column == 0){
                    if(j == 0 ){

                      //  wKey[keyIterator + j + 1] = wKey[keyIterator - blockSize] ^ lastByte[j] ^ RCON[j];
                        wKey[keyIterator] = wKey[keyIterator - blockSize] ^ lastByte[j] ^ RCON[j];


//                        uint8_t test234 = wKey[keyIterator ];
//                        uint8_t test24321 =  wKey[keyIterator - blockSize ] ^ lastByte[j] ^ RCON[j];
//                          uint8_t test2268 =  wKey[keyIterator - blockSize ] ^ lastByte[j] ^ null;
                          keyIterator++;

                    }
                    else {

                      //  wKey[keyIterator + j + 1] = wKey[keyIterator - blockSize + j] ^ lastByte[j] ^ null;
                        wKey[keyIterator ] = wKey[keyIterator - blockSize] ^ lastByte[j] ^ null;


//                        uint8_t tes56t = wKey[keyIterator];
//                        uint8_t test256 =  wKey[keyIterator - blockSize ] ^ lastByte[j] ^ null;
//                          uint8_t test22340 =  wKey[keyIterator - blockSize] ^ lastByte[j] ^ null;
                           keyIterator++;


                    }
                }
               else {
                   // wKey[keyIterator + j + 1] = wKey[keyIterator - blockSize + column] ^ lastByte[j];
                    wKey[keyIterator] = wKey[keyIterator - blockSize] ^ lastByte[j];


//                    uint8_t test13f = wKey[keyIterator ];
//                    uint8_t test2fs =  wKey[keyIterator - blockSize ] ^ lastByte[j];
//                      uint8_t test22g =  wKey[keyIterator - blockSize + j] ^ lastByte[j] ^ null;
                      keyIterator++;
               }

            }

            memcpy(lastByte, wKey + (keyIterator - 4), 4);
        } // конец колонн

       // keyIterator += blockSize;
    } // конец раундов
}

void AES::ShiftRows(uint8_t state[4][4])  {

    for (uint8_t i = 0; i < 4; i++)
    {
        if (i > 0)
        {
            uint8_t row [4];
            for (uint8_t j = 0; j < 4; j++)
            {
                row[j] = state[i][j];
            }

            for (uint8_t j = 0; j < 4; j++)
            {
                state[i][j] = row[(i + j) % 4];
            }
        }
    }
}



void AES::SubBytes(uint8_t state[4][4] )  {



    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            state[i][j] = S_BOX[state[i][j]];
        }
    }

}

void AES::SubBytes(uint8_t key[4] )  {



    for (uint8_t i = 0; i < 4; i++)
    {

            key[i] = S_BOX[key[i]];

    }

}


void AES::MixColumn( uint8_t state[4][4])  {

    static constexpr uint8_t GALOIS_TABLE [4][4]=
    {   {02, 03, 01, 01},
        {01, 02, 03, 01},
        {01, 01, 02, 03},
        {03, 01, 01, 02}  };

    for (int i = 0; i < 4; i++)   //S0 = (2 * S0) ^ (3 * S1) ^ (S2 * 1) ^ (S3 * 1)  example
    {
        uint8_t col [4] = {state[0][i], state[1][i], state[2][i], state[3][i]};

        for(int j = 0;j<4;j++){
        state[j][i] = (col[i] * GALOIS_TABLE[j][i]) ^ (col[i+1] * GALOIS_TABLE[j][i+1]) ^
                      (col[i+1] * GALOIS_TABLE[j][i+1]) ^  (col[i+1] * GALOIS_TABLE[j][i+1]);

        }

    }
}

void AES::AddRoundKey(uint8_t state[4][4], uint8_t roundKey[4][4]) {
    for (int i = 0; i < 4; i++)
           {
               uint32_t* keyPtr = (uint32_t*) roundKey[i];
               uint32_t* statePtr = (uint32_t*) state[i];
               *statePtr ^= *keyPtr;
           }
}


