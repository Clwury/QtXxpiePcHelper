#include <QApplication>
#include "log.h"
#define MAIN 0

#ifdef Q_OS_MACOS
#include "unixlogin.h"
#include "unixhome.h"
#else
#include "winlogin.h"
#include "winhome.h"
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
    MainWindow w;
    w.show();
    // 初始化日志记录
//    logInit();
    return a.exec();
}
