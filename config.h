#ifndef CONFIG_H
#define CONFIG_H

#define PRODUCTION 1
#define USERAGENT "QTGUIAPPLICATION"
#define VERSION "4.3.5"

#if PRODUCTION
    #define BASE "https://int.xxpie.com/api"
    #define BASEDOMAIN "https://www.xxpie.com"
#else
    #define BASE "https://int2.xxpie.com/api"
    #define BASEDOMAIN "https://www-test.xxpie.com"
#endif

#endif // CONFIG_H
