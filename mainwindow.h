#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include "cryptograph.h"
#include "backupmanager.h"
#include "aes.h"
#include <QBitArray>
#include <QTextStream>


#include <settings.h>

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

    void on_pushButtonKeyGen_clicked();

    void on_pushButtonSettings_clicked();

private:
    Settings* settings;

    BackUpManager backUpManager;
    Cryptograph cryptograph;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
