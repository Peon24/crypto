#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   ui->lineDir->setText("C:/Users/FASOL/Desktop/Adobe LC 11/тесттекст");
    ui->lineKey->setText("BETOFKEY2020");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()

{

    backUpManager.copyFilesDir(ui->lineDir->text() , ui->checkBoxCopyFile->checkState()); // копия файлов , не архив

    cryptograph.setKey(ui->lineKey->text());

int counterFiles = 0;
    foreach (QString path , backUpManager.filesDir){



        QFile file(path);

        if(!file.open(QIODevice::ReadOnly)){
            //создать лог и сунуть  ошибку
            continue;
        }

        counterFiles++;

        QByteArray outputByteArray;

        while(!file.atEnd()){
            QByteArray byteArray;
            byteArray = file.read(104857600); // 100mb

         if(ui->comboBox->currentIndex() == 0){

            cryptograph.encryptFileAES(byteArray,outputByteArray);
         }
            else {

            }
        }


        //check encrypt
        file.close();

     QByteArray arr;
     arr = outputByteArray;




        backUpManager.replaceFile( path , outputByteArray ); //удалить , создать, записать в него


        //Пропускать ключ через SHA3 KECCAK , с солью ?

         //записать в лог , время работы , успех, провал
    }



    //lock
    //check
    //backup

}

void MainWindow::on_pushButton_clicked()
{


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    ui->lineDir->setText(dir);
}
