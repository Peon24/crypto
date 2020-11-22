#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CryptoFile");

    setWindowIcon(QIcon(":/png/ICON_CRYPTO.png"));

    ui->lineDir->setText("C:/Users/FASOL/Desktop/Adobe LC 11/тесттекст");
    ui->lineKey->setText("BETOFKEY2020");

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

    bool copyfile = true;// настройки
    fileManager->copyFilesDir(ui->lineDir->text() ,copyfile ); // копия файлов , не архив


    //QQueue , QStack - очень сильно не любят умные указатели
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

    //получим статус шифрования каждого файла
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

    //1)генерация ключа
    //2)проверка корректность шифровки\дешифровки , проблема миссклика
    //3)БАГ c CBC
    //4)логирование
    //5)настройки
    //6)графика
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
    // ui->lineKey->setText(keyGen());
}

void MainWindow::on_pushButtonSettings_clicked()
{

    settings->show();
}

void MainWindow::on_lineKey_textEdited(const QString &arg1)
{
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
          ui->keyCheck->setText("Требуется вернхний регистр");
          break;
      case 3:
          ui->keyCheck->setText("Требуется цифра");
          break;
      case 4:
        ui->keyCheck->setText("Требуется нижний регистр");
        break;


   }
}




















