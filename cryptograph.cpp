#include "cryptograph.h"

Cryptograph::Cryptograph()
{

}
//bool Encrypt::checkKey( const QByteArray& keyInput){

//    return true;
//}

 void Cryptograph::setKey(QString key){




 }

void Cryptograph::encryptFileAES(QByteArray& input , QByteArray& output  ){

    //рзделяем на блоки
    int counterState = std::ceil(input.size() / 16);
    int outputIterator = output.size();
    int inputIterator = 0;

    for (int i = 0; i <= counterState; ++i) {

        uint8_t state[4][4];

                for (uint8_t k = 0; i < 4; i++)
                {
                    for (uint8_t j = 0; j < 4; j++)
                    {
                      if(inputIterator <= input.size()){
                       state[j][k] = input.at(inputIterator);
                       inputIterator++;
                      } else{

                        // здесь нужно добавить что то в стайте....
                          break;
                      }

                    }
                }


//        uint8_t state1[4][4]=
//        {   {static_cast<quint8>(input.at(blockSize * counterState + 0)), static_cast<quint8>(input.at(blockSize * counterState + 4)),
//             static_cast<quint8>(input.at(blockSize * counterState + 8)), static_cast<quint8>(input.at(blockSize * counterState + 12))},



//            {static_cast<quint8>(input.at(blockSize * counterState + 1)), static_cast<quint8>(input.at(blockSize * counterState + 5)),
//             static_cast<quint8>(input.at(blockSize * counterState + 9)), static_cast<quint8>(input.at(blockSize * counterState + 13))},



//            {static_cast<quint8>(input.at(blockSize * counterState + 2)), static_cast<quint8>(input.at(blockSize * counterState + 6)),
//             static_cast<quint8>(input.at(blockSize * counterState + 10)), static_cast<quint8>(input.at(blockSize * counterState + 14))},



//            {static_cast<quint8>(input.at(blockSize * counterState + 3)), static_cast<quint8>(input.at(blockSize * counterState + 7)),
//             static_cast<quint8>(input.at(blockSize * counterState + 11)), static_cast<quint8>(input.at(blockSize * counterState + 15))}  };

         uint8_t encryptedState[16] = { 0 };


         if(i == counterState){

         }

         aes.encrypt(state,encryptedState);


         for(int j = 0; j < 16; j++ ){
             //записываем шифованный файл

              output[outputIterator] = static_cast<qint8>(encryptedState[j]);

             outputIterator++;
         }

    }

}
