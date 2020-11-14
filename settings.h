#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <devicemanagement.h>
#include <QSettings>
//#include <mainwindow.h>

namespace Ui {
class settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:

    static inline const QString ORGANIZATION = "CryptoCorp";
    static inline const QString DOMAIN_APPL = "Crypto";
    static inline const QString APPL = "Crypto";


    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonAddIO_clicked();

    void on_pushButtonAddIO_2_clicked();

private:

     static inline const QString SETTINGS_AUTO_DEL = "settings/auto_delete";
     static inline const QString SETTINGS_ALL_CHECK = "settings/all_check";
     static inline const QString SETTINGS_ALL_IV = "settings/all_iv";

    DeviceManagement device;
    Ui::settings *ui;
};

#endif // SETTINGS_H