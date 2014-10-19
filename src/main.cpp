#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include "MainWindow.h"

using namespace EyeTER::ui;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("zuendmasse");
    QCoreApplication::setOrganizationDomain("zuendmasse.de");
    QCoreApplication::setApplicationName("EyeTER");

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
