#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CryptoFile");

    setWindowIcon(QIcon(":/icon/ICON_CRYPTO.png"));

    ui->lineDir->setText("C:/Users/FASOL/Desktop/Adobe LC 11/тесттекст");
    ui->lineKey->setText("BETOFKEY2020");

    settings = new Settings(this);


}

MainWindow::~MainWindow()
{
    ui->lineKey->setText("XXXXXXXXXXXXXXXXXX");
    delete settings;
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()

{

    bool copyfile = true;// настройки

    fileManager = new FileManager();
    fileManager->copyFilesDir(ui->lineDir->text() ,copyfile ); // копия файлов , не архив


    QByteArray key = ui->lineKey->text().toUtf8();

    QByteArray IV = settings->getSerial("USB").toUtf8();
    IV += settings->getSerial("HDD").toUtf8();


    std::unique_ptr<Cryptograph> cryptograph(new Cryptograph(key,IV));
    ui->lineKey->setText("");



    if(cryptograph){



        foreach ( const QString path , fileManager->m_filesDir){

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


                    if(IV.size() > 0){ // если есть вектор , то не нужно записывать и генерировать , для шифрования
                        isNewFile = !isNewFile;
                    }

                    cryptograph->encryptFileAES(byteArray,outputByteArray,isNewFile);
                    isNewFile = !isNewFile;
                }
                else {

                    cryptograph->decryptFileAES(byteArray,outputByteArray,isNewFile);
                    isNewFile = !isNewFile;

                }

            }


            file.close();


            fileManager->replaceFile(path , outputByteArray );

        }

    }
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
    ui->lineKey->setText(cryptograph->keyGen());
}

void MainWindow::on_pushButtonSettings_clicked()
{

    settings->show();
}
