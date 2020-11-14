#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineDir->setText("C:/Users/FASOL/Desktop/Adobe LC 11/тесттекст");
    ui->lineKey->setText("BETOFKEY2020");

    settings = new Settings(this);
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()

{
    bool copyfile = true;

    backUpManager.copyFilesDir(ui->lineDir->text() ,copyfile ); // копия файлов , не архив

    cryptograph.setKey(ui->lineKey->text());


   // std::vector<int>::const_iterator it;

    foreach ( const QString path , backUpManager.filesDir){



        QFile file(path);

        if(!file.open(QIODevice::ReadOnly)){
            //создать лог и сунуть  ошибку
            continue;
        }

        QByteArray outputByteArray;
        bool isNewFile = true;


        while(!file.atEnd()){
            QByteArray byteArray;
             byteArray = file.read(104857600); // 100mb


            if(ui->comboBox->currentIndex() == 0){

                cryptograph.encryptFileAES(byteArray,outputByteArray,isNewFile);
                isNewFile = !isNewFile;
            }
            else {
                cryptograph.decryptFileAES(byteArray,outputByteArray,isNewFile);
                isNewFile = !isNewFile;
            }

       }

        //check encrypt
        file.close();

        backUpManager.replaceFile( path , outputByteArray );

        //Пропускать ключ через SHA3 KECCAK , с солью ?


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

void MainWindow::on_pushButtonKeyGen_clicked()
{
    ui->lineKey->setText(cryptograph.keyGen());
}

void MainWindow::on_pushButtonSettings_clicked()
{

    settings->show();
}
