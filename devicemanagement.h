#ifndef DEVICEMANAGEMENT_H
#define DEVICEMANAGEMENT_H

#include <windows.h>
#include <QString>
#include <string>


class DeviceManagement
{
public:
    DeviceManagement();
    QString getSerialDevice(QString deviceType);

private:

    QString getSerialFromName(QString fullName);

};

#endif // DEVICEMANAGEMENT_H
