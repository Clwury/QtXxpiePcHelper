QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config.cpp \
    main.cpp \
    mainwindow.cpp \
    networkrequest.cpp

HEADERS += \
    config.h \
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

INCLUDEPATH += $$PWD/qiniu/mac/include
LIBS += -L$$PWD/qiniu/mac/lib -lqiniu

DISTFILES += \
    qss/login.qss
