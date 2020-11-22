#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName(Settings::ORGANIZATION);
    QCoreApplication::setOrganizationDomain(Settings::DOMAIN_APPL);
    QCoreApplication::setApplicationName(Settings::APPL);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
