#ifndef BACKUPMANAGER_H
#define BACKUPMANAGER_H
#include <QString>
#include <QFile>
#include <QDir>
#include <vector>

class BackUpManager
{
public:
    BackUpManager();

    int copyFilesDir(QString path , bool needCopyFiles = false);
    bool checkFiles();
    bool replaceFile(QString path , QByteArray& byteArray );


    int backupFolder();


    std::vector<QString> filesDir;

private:
    void copyFilesRecursion(QString path,QString dst = "");
    bool rezervFiles;
};

#endif // BACKUPMANAGER_H
