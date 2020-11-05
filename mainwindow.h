#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include "encrypt.h"
#include "backupmanager.h"
#include "aes.h"
#include <QBitArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    BackUpManager backUpManager;
    Encrypt encrypt;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
