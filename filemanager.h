#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>
#include <windows.h>

#include <QTextStream>
//#include <algorithm>


class FileManager
{
public:
    FileManager();

    void copyFilesDir(QString path , bool needCopyFiles = false);
    static bool checkFiles(size_t sizeFile ,QString path);

   //static HANDLE openFile(QString path);
   static void getData(QFile &file,QString path,QByteArray &byteArray);
   static void replaceFile(QFile &file , QByteArray& byteArray);


    int backupFolder();


    QMap<QString, size_t> m_filesDir;


private:
    static constexpr size_t GB = 1073741824;

    void copyFilesRecursion(QString path,QString dst = "");
    bool m_rezervFiles;
    quint64 totalSize;
};

#endif // BACKUPMANAGER_H
