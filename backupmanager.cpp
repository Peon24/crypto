#include "backupmanager.h"

BackUpManager::BackUpManager()
{

}


bool BackUpManager::replaceFile(QString path, QByteArray &byteArray){



    //QString typeDoc = path.right(path.findRev("/") + 1);

    QString docType;
    QString fullName;

    //как жаль что я не знаю регулярки )))
    for(int i = path.size()-2; i != 0;i--){

        if(path[i] == "."){
            docType = fullName;
        }

        if(path[i] == "/" ){
            break;
        }

        fullName += path[i];
    }


    QFile::remove(path);
    //безопасно удалить



    // создать новый файл
    QFile file(path);

    if(file.open(QIODevice::WriteOnly)){
        file.write(byteArray);
    }

    //вариант 2
//    QFile file("outfile.dat");
//    file.open(QIODevice::WriteOnly);
//    QDataStream out(&file);

//    Затем используйте

//    QDataStream & QDataStream::writeBytes ( const char * s, uint len )

//    или

//    int QDataStream::writeRawData ( const char * s, int len )

}


int BackUpManager::copyFilesDir(QString path , bool needCopyFiles){

  if(needCopyFiles){
     rezervFiles = true;
  }


  filesDir.clear();
 copyFilesRecursion(path);

}


void BackUpManager::copyFilesRecursion(QString path , QString dst){

    QString currentDir = QDir::currentPath();
    currentDir += "/backup";

    QDir dir(path);
     if (! dir.exists())
         return void();

     foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
         QString dst_path = currentDir + QDir::separator() + d;
         dir.mkpath(dst_path);
         copyFilesRecursion(path+ QDir::separator() + d, dst_path);
     }

     foreach (QString f, dir.entryList(QDir::Files)) {

        if (rezervFiles){
          QFile::copy(path + QDir::separator() + f, dst + QDir::separator() + f);
         }
         filesDir.push_back(path + QDir::separator() + f );

     }

}
