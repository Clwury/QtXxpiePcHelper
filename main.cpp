#include "mainwindow.h"
#include "home.h"

#include <QApplication>
#define MAIN 0


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if MAIN
    home m;
    m.show();
#else
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
