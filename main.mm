//#include "mainwindow.h"
//#include "home.h"
#include "log.h"
#include <QApplication>
#define MAIN 0

#ifdef Q_OS_MACOS
    #include "mainwindow.h"
    #include "unixhome.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//#if MAIN
//#ifdef Q_OS_MACOS
//    unixhome unix_m;
//    unix_m.show();
//#else
//    home m;
//    m.show();
//#endif
//#else
//    MainWindow w;
//    w.show();
//#endif
#ifdef Q_OS_MACOS
    #if MAIN
        unixhome unix_m;
        unix_m.show();
    #else
        MainWindow w;
        w.show();
    #endif
    // 初始化日志记录
//    logInit();
#endif
    return a.exec();
}
