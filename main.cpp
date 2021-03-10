#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScreen *screen = a.primaryScreen();
    qDebug() << screen->size();
    MainWindow w;
    w.move((screen->size().width() - w.width()) / 2, (screen->size().height() - w.height()) / 2);
    w.show();
    return a.exec();
}
