#include "mainwindow.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QObject::connect(&w, &MainWindow::appExit, &a, &QApplication::quit);
    return a.exec();
}
