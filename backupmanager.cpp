#include "backupmanager.h"

BackUpManager::BackUpManager()
{

}


bool BackUpManager::replaceFile(QString path, QByteArray &byteArray){

    QString docType;
    QString fullName;




    QFile::remove(path);
    //безопасно удалить



    // создать новый файл
    QFile file(path);

    if(file.open(QIODevice::WriteOnly)){
        file.write(byteArray);
    }



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
