#include <QApplication>
#include <QMainWindow>
#include <QDebug>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    qDebug() << "Hello World";

    MainWindow mainWin;
    mainWin.show();

    return app.exec();
}
