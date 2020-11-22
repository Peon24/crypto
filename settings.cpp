#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);


   device = new DeviceManagement();

    QSettings settings(ORGANIZATION, APPL);
}

Settings::~Settings()
{
    delete device;
    delete ui;
}

QString Settings::getSerial(QString deviceType){

    if (deviceType == "USB"){
    if(ui->lineEditSerialUSB->text() != ""){
        return ui->lineEditSerialUSB->text();
       }
    }


    if(deviceType == "HDD"){
        if(ui->lineEditSerialHDD->text() != ""){
            return ui->lineEditSerialHDD->text();
        }
    }

    return "";
}

void Settings::on_pushButtonSave_clicked()
{
    // запись в файл конфига
    //сигнал что нужно обновить конфиг в криптографе


    QSettings settings(ORGANIZATION, APPL);


//    if(ui->checkBoxAutoDel->isChecked()){
//        settings.setValue(SETTINGS_TRAY, true);
//    } else {
//        settings.setValue(SETTINGS_TRAY, false);
//    }
    settings.sync();

    this->close();
}

void Settings::on_pushButtonCancel_clicked()
{
    this->close();
}

void Settings::on_pushButtonAddIO_clicked()
{   

    if(ui->lineEditSerialUSB->text() != ""){
         ui->pushButtonAddIO->setText("Добавить");
         ui->lineEditSerialUSB->setText("");
         return void();

    }

   ui->lineEditSerialUSB->setText(device->getSerialDevice("USB"));

   if(ui->lineEditSerialUSB->text() == ""){

       QMessageBox msgBox;
       msgBox.setWindowIcon(QIcon(QPixmap(":/png/5.png")));
       msgBox.setWindowTitle("Ошибка");
       msgBox.setIconPixmap(QPixmap(":/gifs/resent.gif"));
       msgBox.setText("Не удалось обнаружить устройство");
       msgBox.exec();
   } else {

        ui->pushButtonAddIO->setText("Удалить");
   }


}

void Settings::on_pushButtonAddIO_2_clicked()
{

    if(ui->lineEditSerialHDD->text() != ""){
         ui->pushButtonAddIO_2->setText("Добавить");
         ui->lineEditSerialHDD->setText("");
         return void();
    }


     ui->lineEditSerialHDD->setText(device->getSerialDevice("SCSI"));

     if(ui->lineEditSerialHDD->text() == ""){

     QMessageBox msgBox;
     msgBox.setWindowIcon(QIcon(QPixmap(":/png/5.png")));
     msgBox.setWindowTitle("Ошибка");
     msgBox.setIcon(QMessageBox::Critical);
     msgBox.setText("Не удалось обнаружить устройство");
     msgBox.exec();

     }else{
         ui->pushButtonAddIO_2->setText("Удалить");
     }
}
