#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);

    QSettings settings(ORGANIZATION, APPL);
}

Settings::~Settings()
{
    delete ui;
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

   ui->lineEditSerialUSB->setText(device.getSerialDevice("USB"));
}

void Settings::on_pushButtonAddIO_2_clicked()
{
     ui->lineEditSerialHDD->setText(device.getSerialDevice("SCSI"));
}
