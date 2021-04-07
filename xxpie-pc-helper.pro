QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    networkrequest.cpp

HEADERS += \
    config.h \
    home.h \
    mainwindow.h \
    networkrequest.h

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

unix {
    INCLUDEPATH += $$PWD/qiniu/mac/include
    LIBS += -L$$PWD/qiniu/mac/lib -lqiniu
}

win32 {
    INCLUDEPATH += $$PWD/qiniu/win/include
    LIBS += -L$$PWD/qiniu/win/bin -lqiniu
    LIBS += -L$$PWD/ssl -llibcrypto-1_1
    LIBS += -L$$PWD/ssl -llibssl-1_1
}


DISTFILES += \
    qss/login.qss
