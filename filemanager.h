#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>


class FileManager
{
public:
    FileManager();

    void copyFilesDir(QString path , bool needCopyFiles = false);
    bool checkFiles();
   static void replaceFile(QString path , QByteArray& byteArray);


    int backupFolder();


    QMap<QString, size_t> m_filesDir;


private:
    static constexpr size_t GB = 1073741824;

    void copyFilesRecursion(QString path,QString dst = "");
    bool m_rezervFiles;
    quint64 totalSize;
};

#endif // BACKUPMANAGER_H
