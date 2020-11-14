#include "devicemanagement.h"




DeviceManagement::DeviceManagement()
{

}


QString DeviceManagement::getSerialDevice(QString deviceType){


static constexpr int TOTALBYTES  = 300; //8192;



    QString pathStr = "\SYSTEM\\CurrentControlSet\\Services\\disk\\Enum";
    LPCWSTR pathLPCW = (const wchar_t*) pathStr.utf16();


    HKEY hKey;
    if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, pathLPCW, 0, KEY_QUERY_VALUE , &hKey) != ERROR_SUCCESS){
        return "Error";
    }

    //Read & save
    DWORD BufferSize = TOTALBYTES;
    DWORD cbData;
    DWORD dwRet;

    LPBYTE data = (LPBYTE)malloc(BufferSize);

    cbData = BufferSize;

    DWORD typeB = REG_BINARY;

    QString field = "Count";
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
                for(int i =0;i< BufferSize;i++){
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

    //Close registry
    RegCloseKey(hKey);
    return "Error";

}


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






//HDEVINFO deviceInfoSet;
//GUID *guidDev = (GUID*) &GUID_DEVCLASS_USB;
//deviceInfoSet = SetupDiGetClassDevs(guidDev, NULL, NULL, DIGCF_PRESENT | DIGCF_PROFILE);
//TCHAR buffer [4000];
//int memberIndex = 0;

//std::vector<QString> vec;
//while (true)
//        {
//        SP_DEVINFO_DATA deviceInfoData;
//        ZeroMemory(&deviceInfoData, sizeof(SP_DEVINFO_DATA));
//        deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
//        if (SetupDiEnumDeviceInfo(deviceInfoSet, memberIndex, &deviceInfoData) == FALSE)
//                {
//                if (GetLastError() == ERROR_NO_MORE_ITEMS)
//                        {
//                        break;
//                        }
//                }
//        DWORD nSize=0 ;
//        SetupDiGetDeviceInstanceId (deviceInfoSet, &deviceInfoData, buffer, sizeof(buffer), &nSize);
//        buffer [nSize] ='\0';
//        //_tprintf (_T("%s\n"), buffer);
//        memberIndex++;
//        //Label1->Caption=String(buffer);


//if (deviceInfoSet)
//        {

//        SetupDiDestroyDeviceInfoList(deviceInfoSet);

//        }

//QString str = "";
//for(int i = 0;i<10;i++){
//    str += buffer[i];
//}

// vec.push_back(str);


// }

//vec.push_back("конец");









//dfdfdfdfdddddddddddddddddddddddddddd


//The serial number is the subkey under HKLM\SYSTEM\CCS\Enum\USB\Vid_xxxx&Pid_yyyy

//аппаратный том
//DWORD DeviceManagement::GetPhysicalDriveSerialNumber(UINT nDriveNumber IN, std::string strSerialNumber OUT)
//{
//    DWORD dwRet = NO_ERROR;
//    //strSerialNumber.Empty();

//    // Format physical drive path (may be '\\.\PhysicalDrive0', '\\.\PhysicalDrive1' and so on).
//    QString strDrivePath = "\\\\.\\PhysicalDrive0";

//    //strDrivePath.Format(("\\\\.\\PhysicalDrive%u"), nDriveNumber);

//    // Get a handle to physical drive
//    HANDLE hDevice = nullptr;
//    LPCWSTR strDrivePathWSTR = (const wchar_t*) strDrivePath.utf16();

//    //открываем физический диск
//    hDevice = CreateFile(strDrivePathWSTR, 0, FILE_SHARE_READ|FILE_SHARE_WRITE,
//                                  NULL, OPEN_EXISTING, 0, NULL);

//    if(INVALID_HANDLE_VALUE == hDevice)
//        return ::GetLastError();

//    // Set the input data structure
//    STORAGE_PROPERTY_QUERY storagePropertyQuery;
//   // заполняет блок памяти нулями.
//    ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
//    storagePropertyQuery.PropertyId = StorageDeviceProperty;
//    storagePropertyQuery.QueryType = PropertyStandardQuery;

//    // Get the necessary output buffer size
//    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = {0};
//    DWORD dwBytesReturned = 0;
//    if(! ::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
//                           &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
//                           &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
//                           &dwBytesReturned, NULL))
//    {
//        dwRet = ::GetLastError();
//        ::CloseHandle(hDevice);
//        return dwRet;
//    }

//    // Выделить выходной буфер
//    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
//    BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
//    ZeroMemory(pOutBuffer, dwOutBufferSize);

//    // Получить дескриптор устройства хранения
//    if(! ::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
//                           &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
//                           pOutBuffer, dwOutBufferSize,
//                           &dwBytesReturned, NULL))
//    {
//        dwRet = ::GetLastError();
//        delete []pOutBuffer;
//        ::CloseHandle(hDevice);
//        return dwRet;
//    }

//    // Теперь выходной буфер указывает на структуру STORAGE_DEVICE_DESCRIPTOR
//    // следует дополнительная информация, такая как идентификатор поставщика, идентификатор продукта, серийный номер и т. д.
//    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
//    const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
//    if(dwSerialNumberOffset != 0)
//    {
//        // Finally, get the serial number

//     auto strSerialNumber1 = pOutBuffer + dwSerialNumberOffset;


//    }


//    delete []pOutBuffer;
//    ::CloseHandle(hDevice);
//    return dwRet;
//}

