#include "cryptograph.h"


Cryptograph::Cryptograph(QByteArray &key , QByteArray &IV , QString encryptionType)
{

    if(encryptionType == "AES"){

        if(m_aes.setKey(key)){

            if(IV.size() > 0){
                m_aes.convertAndSetIV(IV);
            }

            m_aes.getPointersToLock(m_memoryManager.getLockPtrs());
            m_memoryManager.lockAll();

        }
    }

}


Cryptograph::~Cryptograph()
{

}


int Cryptograph::checkKey( const QString &key){
    return AES::checkKey(key);
}


int Cryptograph::start(QString path, bool encrypt, size_t sizeFile , bool needIV){


    QFile file(path);

    if(!file.open(QIODevice::ReadWrite)){
        //создать лог и сунуть  ошибку
        return 1;
    }

    bool isNewFile = true;

    QByteArray output;


    while(!file.atEnd()){

        QByteArray byteArray;

        FileManager::getData(file,byteArray);

        if(encrypt){

            if(!needIV){ // если есть вектор , то не нужно записывать и генерировать , для шифрования
                isNewFile = !isNewFile;
            }

            encryptFileAES(byteArray,output,isNewFile);

            if(file.atEnd()) {
                writeNeedDelete(output,sizeFile);
            }

            isNewFile = !isNewFile;
        }
        else {

            if(!needIV){ // если есть вектор , то не нужно записывать и генерировать , для шифрования
                isNewFile = !isNewFile;
            }

            decryptFileAES(byteArray,output,isNewFile);

            isNewFile = !isNewFile;

        }

    }

    FileManager::replaceFile(file,output);

    return 0;

}

void Cryptograph::writeNeedDelete(QByteArray& input , size_t size){

    uint8_t countDeleteNull = 16 - ( size % blockSize );

    input.append(countDeleteNull);

}

QString Cryptograph::keyGen(){

    return AES::generateKey();
}



void Cryptograph::encryptFileAES(QByteArray& input , QByteArray& output , bool isNewFile ){

    //делим на блоки

    int counterState = std::ceil((float)input.size() / 16);
    int inputIterator = 0;

    uint8_t encryptedState[blockSize] = { 0 };

    if(isNewFile){
        m_aes.newFile(encryptedState,true);

        for(int j = 0; j < 16; j++ ){
            output.append(encryptedState[j]);
        }

    }

    for (int i = 1; i <= counterState; i++) {

        uint8_t state[4][4];

        for (uint8_t k = 0; k < 4; k++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if(inputIterator < input.size()){

                    state[j][k] = input.at(inputIterator);
                    inputIterator++;
                } else{

                    state[j][k] = 0; // здесь нужно добавить что то в блок  , чтобы стало ровно 16 байт
                    //возможно нужно  воровать у прошлого блока кусок

                }

            }
        }

        std::fill(encryptedState, encryptedState + 16, 0);

        m_aes.encrypt(state,encryptedState );

        for(int j = 0; j < 16; j++ ){
            //записываем шифованный файл
            output.append(encryptedState[j]);
        }

    }

}


void Cryptograph::decryptFileAES(QByteArray &input, QByteArray &output, bool isNewFile){
    //рзделяем на блоки
    int counterState = std::ceil((float)(input.size()-1) / blockSize);
    int inputIterator = 0;

    uint8_t encryptedState[blockSize] = { 0 };

    uint8_t deleteLastNull = input.at(input.size()-1);

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
                    //проблема, должно делится ровно
                    break;
                }

            }
        }

        QString str;
        for(int i = 0;i<16;i++){

               str += IV[i];

        }

        str = str;

        m_aes.newFile(IV,false); //добавляем в АЕС вектор инициализации

    }

    for (int i = 2; i <= counterState; i++) {

        uint8_t state[4][4];

        for (uint8_t k = 0; k < 4; k++)
        {
            for (uint8_t j = 0; j < 4; j++)
            {
                if(inputIterator < input.size() - 1 ){ // - deleteLastNull

                    state[j][k] = input.at(inputIterator);

                    inputIterator++;
                } else{
                    //если блок не делится на 16 без остатка, то у нас проблемы
                    break;
                }

            }
        }

        std::fill(encryptedState, encryptedState + blockSize, 0);

        m_aes.decrypt(state,encryptedState );

        if(i!= counterState){
            for(int j = 0; j < 16; j++ ){

                output.append(encryptedState[j]);

            }
        } else{

            for(int j = 0; j < (16 - deleteLastNull); j++ ){

                output.append(encryptedState[j]);

            }

        }



    }
}
