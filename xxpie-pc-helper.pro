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
    config.cpp \
    customsearchbar.cpp \
    home.cpp \
    imageview.cpp \
    itemdelegate.cpp \
    log.cpp \
    main.mm \
#    mainwindow.mm \
    networkrequest.cpp

HEADERS += \
    config.h \
    customsearchbar.h \
    home.h \
#    mainwindow.h \
    imageview.h \
    itemdelegate.h \
    log.h \
    networkrequest.h \

macx {
    OBJECTIVE_HEADERS += unixhome.h \
                        mainwindow.h
    OBJECTIVE_SOURCES += unixhome.mm \
                        mainwindow.mm
}

TRANSLATIONS += \
    xxpie-pc-helper_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui

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
