#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H
#include <QString>
#include <QFile>
#include <QDir>
#include <vector>

class FileManager
{
public:
    FileManager();

    void copyFilesDir(QString path , bool needCopyFiles = false);
    bool checkFiles();
    void replaceFile(QString path , QByteArray& byteArray);



    int backupFolder();


    std::vector<QString> m_filesDir;

private:
    void copyFilesRecursion(QString path,QString dst = "");
    bool m_rezervFiles;
    int totalSize;
};

#endif // BACKUPMANAGER_H
