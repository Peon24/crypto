#include "filemanager.h"

FileManager::FileManager()
{
    totalSize = 0;
}


void FileManager::replaceFile(QString path, QByteArray &byteArray){

    QString docType;
    QString fullName;


    QFile::remove(path);
    //безопасно удалить

    // создать новый файл
    QFile file(path);

    if(file.open(QIODevice::WriteOnly)){
        file.write(byteArray);
    }

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

    //     foreach (QString f, dir.entryList(QDir::Files)) {

    //        if (m_rezervFiles){
    //          QFile::copy(path + QDir::separator() + f, dst + QDir::separator() + f);
    //         }
    //         m_filesDir.push_back(path + QDir::separator() + f );

    //     }
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
        m_filesDir.push_back(path + QDir::separator() + i.fileName() );
        }

        totalSize += i.size();
    }

}
