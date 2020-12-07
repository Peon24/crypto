#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include "cryptograph.h"
#include <queue>
#include <stack>
#include <future>

#include <settings.h>
#include <log.h>

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

    void on_lineKey_textEdited(const QString &arg1);

private:
    Settings* settings;
    Log *log;

    //Cryptograph* cryptograph;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
