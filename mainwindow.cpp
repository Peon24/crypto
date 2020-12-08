#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CryptoFile");
    setWindowIcon(QIcon(":/png/ICON_CRYPTO.png"));

    settings = new Settings(this);
    log = new Log(this);

}

MainWindow::~MainWindow()
{
    ui->lineKey->setText("XXXXXXXXXXXXXXXXXX");

    delete settings;
    delete log;
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()

{
    log->startMovie();

    if(Cryptograph::checkKey(ui->lineKey->text()) != 0){
        ui->status->setText("Ключ слишком простой");
    }

    QByteArray key = ui->lineKey->text().toUtf8();

    QByteArray IV;
        if(settings->getSerial("USB") != ""){
         IV = settings->getSerial("USB").toUtf8();
        }

        if(settings->getSerial("HDD") != ""){
        IV += settings->getSerial("HDD").toUtf8();
        }



    bool needIV;
    if(IV.size() ==  0){
        needIV = true;
    }


    bool encrypt;
    if(ui->comboBox->currentIndex() == 0){
        encrypt = true;
    } else{
        encrypt = false;
    }

    std::unique_ptr<FileManager> fileManager(new FileManager());

    bool copyFile = settings->copy();// настройки

    fileManager->copyFilesDir(ui->lineDir->text() ,copyFile ); // копия файлов , не архив

    std::queue<std::future<int>> queueTask;
    std::stack<std::unique_ptr<Cryptograph>> stackCrypt;

    QMap<QString, size_t>::const_iterator itPath = fileManager->m_filesDir.constBegin();
    while (itPath != fileManager->m_filesDir.constEnd()) {

        QString path = itPath.key();
        size_t  size = itPath.value();

        stackCrypt.push(std::make_unique<Cryptograph>(key,IV));
        queueTask.push(std::async(std::launch::async,&Cryptograph::start,std::move(stackCrypt.top()),path,encrypt,size ,needIV));

        itPath++;

    }

    //получим статус каждого файла
            while(!queueTask.empty()){
                auto &task = queueTask.front();
                bool status = task.get();
                queueTask.pop();
            }


            log->stopMovie();
            if(encrypt){
            ui->status->setText("Зашифровано");
            } else {
            ui->status->setText("Дешифровано");
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
    ui->lineKey->setText(Cryptograph::keyGen());
}

void MainWindow::on_pushButtonSettings_clicked()
{

    settings->show();
}

void MainWindow::on_lineKey_textEdited(const QString &arg1)
{
   if(ui->comboBox->currentIndex() == 1){ // при дешифровании не проверяем ключ
       return void();
   }

   int status = Cryptograph::checkKey(arg1);

   switch (status)
   {
      case 0:
          ui->keyCheck->setText("");
       break;
      case 1:
         ui->keyCheck->setText("Слкишком короткий ключ");
         break;
      case 2:
          ui->keyCheck->setText("Требуется верхний регистр");
          break;
      case 3:
          ui->keyCheck->setText("Требуется цифра");
          break;
      case 4:
        ui->keyCheck->setText("Требуется нижний регистр");
        break;
      case 5:
        ui->keyCheck->setText("Введите ключ");
        break;


   }
}




















