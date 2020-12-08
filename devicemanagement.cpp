#include "devicemanagement.h"


DeviceManagement::DeviceManagement()
{

}

// здесь читаем из реестра, подключенный серийник флешки или жесткого диска
QString DeviceManagement::getSerialDevice(QString deviceType){


    static constexpr int TOTALBYTES  = 300;

    const QString pathStr = "\SYSTEM\\CurrentControlSet\\Services\\disk\\Enum";
    LPCWSTR pathLPCW = (const wchar_t*) pathStr.utf16();


    HKEY hKey;
    if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, pathLPCW, 0, KEY_QUERY_VALUE , &hKey) != ERROR_SUCCESS){
        return "";
    }


    DWORD BufferSize = TOTALBYTES;
    DWORD cbData;
    DWORD dwRet;

    LPBYTE data = (LPBYTE)malloc(BufferSize);

    cbData = BufferSize;

    DWORD typeB = REG_BINARY;

    const QString field = "Count";
    LPCWSTR fieldCountLPCW = (const wchar_t*) field.utf16();


    dwRet = ::RegQueryValueEx(hKey, fieldCountLPCW, NULL, &typeB, data, &cbData);

    if(dwRet == ERROR_SUCCESS){
        int count = data[0];

        for(int i = 0;i < count;i++){


            QString field = QString::number(i);
            LPCWSTR fieldLPCW = (const wchar_t*) field.utf16();

            cbData = BufferSize;
            dwRet = ::RegQueryValueEx(hKey, fieldLPCW, NULL, &typeB, data, &cbData);
            if(dwRet == ERROR_SUCCESS){

                QString nameDevice;
                for(int i =0; i < BufferSize;i++){
                    if(data[i] != NULL)
                        nameDevice += data[i];
                }

                QString check;
                for(int k =0;k<10;k++){
                    if(nameDevice[k] != "\\"){
                        check += nameDevice[k];
                    } else{
                        break;
                    }
                }

                if(check == deviceType){

                    RegCloseKey(hKey);
                    return getSerialFromName(nameDevice);
                }


            }

        }

    }


    RegCloseKey(hKey);
    return "";

}

//парсим имя устройства, получая серийник
QString DeviceManagement::getSerialFromName(QString fullName){

    int pos = fullName.lastIndexOf(QChar('&'));

    QString longName = fullName.left(pos);

    QString serial;
    for(int i = longName.length()-1; i>= 0;i--){
        if(longName[i]== "\\"){
            break;
        }

        serial += longName[i];
    }

  std::reverse(serial.begin(), serial.end());

    return  serial;
}





