#include "encrypt.h"

Encrypt::Encrypt()
{

}
bool Encrypt::checkKey( const QByteArray& keyInput){

    return true;
}

 void Encrypt::setKey(QByteArray keyInput){
     if(checkKey(keyInput)){
         //конвертируем ключ

         memset(key,0,16);

         for(int i = 0 ; i < keyInput.length(); i++ ){
             key[i] = keyInput[i];

         }
     }
 }

void Encrypt::encryptFile(QByteArray& input , QByteArray& output  ){

    //рзделяем на блоки
    int counterState = std::ceil(input.size() / 16);
    int outputIterator = output.size(); // здесь может сбится порядок 0 1 2 3

    for (int i = 0; i < counterState; ++i) {


         //ДЕЛАЕМ ВОТ ТАК

//         uint8_t state[4][4]=
//         {   {input[0], input[4], input[8], input[12]},
//             {input[1], input[5], input[9], input[13]},
//             {input[2], input[6], input[10], input[14]},
//             {input[3], input[7], input[11], input[15]}  };

         //state[4][4]
         uint8_t state[4][4]=
         {   {static_cast<quint8>(input.at(0)), static_cast<quint8>(input.at(4)),
              static_cast<quint8>(input.at(8)), static_cast<quint8>(input.at(12))},



             {static_cast<quint8>(input.at(1)), static_cast<quint8>(input.at(5)),
              static_cast<quint8>(input.at(9)), static_cast<quint8>(input.at(13))},



             {static_cast<quint8>(input.at(2)), static_cast<quint8>(input.at(6)),
              static_cast<quint8>(input.at(10)), static_cast<quint8>(input.at(14))},



             {static_cast<quint8>(input.at(3)), static_cast<quint8>(input.at(7)),
              static_cast<quint8>(input.at(11)), static_cast<quint8>(input.at(15))}  };

         uint8_t encryptedState[16] = { 0 };

         this->encrypt(state,this->key,encryptedState);


         for(int j = 0; j < 16; j++ ){
             //записываем шифованный файл
            // output[outputIterator] = static_cast<quint8>(encryptedState[j]);
              output[outputIterator] = static_cast<qint8>(encryptedState[j]);
              output[outputIterator] = encryptedState[j];
             outputIterator++;
         }

    }

}
