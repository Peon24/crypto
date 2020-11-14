#include "cryptograph.h"

Cryptograph::Cryptograph()
{

}
//bool Encrypt::checkKey( const QByteArray& keyInput){

//    return true;
//}

 void Cryptograph::setKey(QString key){


 }

 QString Cryptograph::keyGen(){

    return aes.generateKey();
 }

void Cryptograph::encryptFileAES(QByteArray& input , QByteArray& output , bool isNewFile ){

    //рзделяем на блоки
    int counterState = std::ceil(input.size() / 16);
    int inputIterator = 0;

     uint8_t encryptedState[16] = { 0 };

    if(isNewFile){
        aes.newFile(encryptedState,true);

        for(int j = 0; j < 16; j++ ){
         output.append(static_cast<qint8>(encryptedState[j]));
        }

    }
    for (int i = 1; i <= counterState; ++i) {

        uint8_t state[4][4];


                for (uint8_t k = 0; k < 4; k++)
                {
                    for (uint8_t j = 0; j < 4; j++)
                    {
                      if(inputIterator < input.size()){

                       state[j][k] = input.at(inputIterator);
                       inputIterator++;
                      } else{
                         state[j][k] = 0;
                        // здесь нужно добавить что то в блок  , чтобы стало ровно 16 байт
                          break;
                      }

                    }
                }


         std::fill(encryptedState, encryptedState + 16, 0);

         aes.encrypt(state,encryptedState );


         for(int j = 0; j < 16; j++ ){
             //записываем шифованный файл
               output.append(encryptedState[j]);
         }

    }

}

//___________________Decrypt_________________________


void Cryptograph::decryptFileAES(QByteArray &input, QByteArray &output, bool isNewFile){
    //рзделяем на блоки
    int counterState = std::ceil(input.size() / blockSize);
    int inputIterator = 0;


    uint8_t encryptedState[blockSize] = { 0 };

    if(isNewFile){ // не брать IV , если флешка

        uint8_t IV[blockSize];

        for (uint8_t k = 0; k < 4; k++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if(inputIterator < input.size()){
                    IV[(k * 4) + j] = input.at(inputIterator);
                    inputIterator++;
                } else{
                    //проблема
                    break;
                }

            }
        }


        aes.newFile(IV,false); //добавляем в АЕС вектор инициализации

        counterState--;
    }

    for (int i = 1; i <= counterState; ++i) {

        uint8_t state[4][4];

        for (uint8_t k = 0; k < 4; k++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if(inputIterator < input.size()){

                    state[j][k] = input.at(inputIterator);

                    inputIterator++;
                } else{
                   //если блок не делится на 16 без остатка, то у нас проблемы
                    break;
                }

            }
        }

        std::fill(encryptedState, encryptedState + blockSize, 0);

            aes.decrypt(state,encryptedState );

        for(int j = 0; j < 16; j++ ){

              output.append(encryptedState[j]);

        }

    }
}
