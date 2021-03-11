#ifndef CONFIG_H
#define CONFIG_H

#include <QUuid>
#include <QString>
#include <QDebug>

#define PRODUCTION 1
#define USERAGENT "QTGUIAPPLICATION"
#define PLATFORM "PC_HELPER"
#define VERSION "4.3.5"
#define TIMEOUT 30000

#if PRODUCTION
    #define BASE "https://int.xxpie.com/api"
    #define BASEDOMAIN "https://www.xxpie.com"
#else
    #define BASE "https://int2.xxpie.com/api"
    #define BASEDOMAIN "https://www-test.xxpie.com"
#endif

extern const QUuid UUID;
extern const QString MACHINE_ID;

#endif // CONFIG_H
