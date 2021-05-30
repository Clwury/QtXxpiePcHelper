QT       += core gui network

macx {
    QT += macextras
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_NO_DEBUG_OUTPUT
DEFINES += QT_MESSAGELOGCONTEXT
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    albumitemdelegate.cpp \
    config.cpp \
    customsearchbar.cpp \
    imageview.cpp \
    itemdelegate.cpp \
    log.cpp \
    networkrequest.cpp \

HEADERS += \
    albumitemdelegate.h \
    config.h \
    customsearchbar.h \
    imageview.h \
    itemdelegate.h \
    log.h \
    networkrequest.h \

macx {
    OBJECTIVE_HEADERS += \
        unixlogin.h \
        unixhome.h
    OBJECTIVE_SOURCES += \
        main.mm \
        unixhome.mm \
        unixlogin.mm
}

win32 {
    HEADERS += \
        winlogin.h \
        winhome.h
    SOURCES += \
        main.cpp \
        winhome.cpp \
        winlogin.cpp
}

TRANSLATIONS += \
    xxpie-pc-helper_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    winlogin.ui

RESOURCES += \
    resource.qrc

macx {
    INCLUDEPATH += $$PWD/qiniu/mac/include
    LIBS += -L$$PWD/qiniu/mac/lib -lqiniu

    LIBS += -framework Foundation
    LIBS += -framework AppKit
}

win32 {
    INCLUDEPATH += $$PWD/qiniu/win/include
    LIBS += -L$$PWD/qiniu/win/bin -lqiniu
    LIBS += -L$$PWD/ssl -llibcrypto-1_1
    LIBS += -L$$PWD/ssl -llibssl-1_1
}


DISTFILES += \
    qss/login.qss
