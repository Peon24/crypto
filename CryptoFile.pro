QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O3
QMAKE_CXXFLAGS_RELEASE += -O0

QMAKE_CFLAGS_RELEASE -= -O1
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE -= -O3
QMAKE_CFLAGS_RELEASE += -O0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aes.cpp \
    cryptograph.cpp \
    devicemanagement.cpp \
    filemanager.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    memorymanager.cpp \
    settings.cpp

HEADERS += \
    aes.h \
    cryptograph.h \
    devicemanagement.h \
    filemanager.h \
    log.h \
    mainwindow.h \
    memorymanager.h \
    settings.h

FORMS += \
    log.ui \
    mainwindow.ui \
    settings.ui

win32 {

LIBS += -lhid -lsetupapi -lKernel32

}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
