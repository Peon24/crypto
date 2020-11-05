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
    AES aes;

    QByteArray key = ui->lineKey->text().toUtf8();

    //aes.checkKey(ui->lineKey->text());

    backUpManager.copyFilesDir(ui->lineDir->text() , ui->checkBoxCopyFile->checkState()); // копия файлов , не архив

    // static constexpr int  STATE_SIZE = 128;


    encrypt.setKey(key);


    foreach (QString path , backUpManager.filesDir){


        //для больших файлов нужен цикл

//        while (!file.atEnd()) {
//          blob = file.read(pass.length() * 1024);
//          for (int i = 0; i < blob.size(); i++) {
//                res.push_back(blob[i] ^ pass[i % pass.length()].toAscii());
//          }
//        }

        QFile file(path);

        if(!file.open(QIODevice::ReadOnly)){
            //создать лог и сунуть  лог ошибку
            continue;
        }

        QByteArray encryptedByteArray;

        int teste[10000];
        QString str;

        while(!file.atEnd()){
            //падает производительность с ключом , оутпут += ,
            QByteArray byteArray;
            byteArray = file.read(104857600); // 100mb
            for(int i = 0; i < byteArray.size(); i++){
                teste[i] = byteArray[i];

            }
             //QString s = QString::fromUtf8(byteArray);
//            QByteArray arr1;
//            arr1 = byteArray;
            encrypt.encryptFile(byteArray,encryptedByteArray); //проверить на сайз
        }


        //check encrypt
        file.close();

     QByteArray arr;
     arr = encryptedByteArray;


     QString s = QString::fromUtf8(encryptedByteArray);

        backUpManager.replaceFile( path , encryptedByteArray ); //удалить , создать, записать в него
        //записать просто цифры ? а при дешифровке все должно вернуться
        //a размер увеличится
        //б как потом обрабатывать
        //с может переводить обратно в цифры?


        //не включать в ключ первые 4 колонны?


        //писать дешифровку, сейчас у меня режим CBC ? разобраться
        //дополнительные алгоритмы
        //XTS
        //Генерация ключа с двоичным могомерным вектором

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
