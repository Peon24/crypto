QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Settings

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aes.cpp \
    backupmanager.cpp \
    cryptograph.cpp \
    devicemanagement.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    sha3.cpp

HEADERS += \
    aes.h \
    backupmanager.h \
    cryptograph.h \
    devicemanagement.h \
    mainwindow.h \
    settings.h \
    sha3.h

FORMS += \
    mainwindow.ui \
    settings.ui

win32 {

LIBS += -lhid -lsetupapi

}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
