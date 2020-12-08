#include "filemanager.h"

FileManager::FileManager()
{
totalSize = 0;
}



void FileManager::getData(QFile &file,QByteArray &byteArray){

    byteArray = file.read(16000000); //16 mb

}

bool FileManager::checkFiles(size_t size,QString path){

    std::reverse(path.begin(), path.end());

    QString fileName;
    for(int i = 0; i < path.length();i++){
        if(path[i] == QDir::separator()) {
            break;
        }
        fileName += path[i];
    }

    QString pathBackup = QDir::currentPath() + QDir::separator() + "/backup";
    pathBackup += QDir::separator() + fileName;

    size_t sizeBackupFile = QFileInfo(pathBackup).size(); // получили размер сохраненного файла


    if (sizeBackupFile == size){
        return true;
    }else{
        return false;
    }

}


void FileManager::replaceFile(QFile &file, QByteArray &byteArray){

    file.resize(0);
    file.write(byteArray);
    file.close();

}


void FileManager::copyFilesDir(QString path , bool needCopyFiles){

    if(needCopyFiles){
        m_rezervFiles = true;
    }


    m_filesDir.clear();
    copyFilesRecursion(path);

}


void FileManager::copyFilesRecursion(QString path , QString dst){

    static QString currentDir = QDir::currentPath();
    currentDir += "/backup";

    QDir dir(path);
    if (! dir.exists())
        return void();


    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = currentDir + QDir::separator() + d;
        dir.mkpath(dst_path);
        copyFilesRecursion(path+ QDir::separator() + d, dst_path);
    }

    QFileInfoList folderitems( dir.entryInfoList() );

    foreach ( QFileInfo i, folderitems ) {
        QString iname( i.fileName() );
        if ( iname == "." || iname == ".." || iname.isEmpty() ){
            continue;
        }

        if (m_rezervFiles){
            QFile::copy(path + QDir::separator() + i.fileName(), dst + QDir::separator() + i.fileName());
        }
        if(i.isFile()){
            m_filesDir.insert(path + QDir::separator() + i.fileName(),i.size()  );
        }

        totalSize += i.size();
    }

}
