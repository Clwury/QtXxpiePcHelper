QT += \
   quick \
   widgets

CONFIG += \
       c++11 \
       qmltypes

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend.cpp \
        main.cpp \
        piechart.cpp \
        mainwindow.cpp \
        randomnumbergenerator.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    QtQuickXxpie-pc-helper_zh_CN.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =
#QML_IMPORT_NAME = io.qt.examples.backend
#QML_IMPORT_VERSION = 1
#QML_IMPORT_NAME = io.qt.examples.randomnumbergenerator
#QML_IMPORT_VERSION = 1
QML_IMPORT_NAME = Charts
QML_IMPORT_VERSION = 1

QML_IMPORT_PATH = $$PWD
#INCLUDEPATH += io/qt/examples/randomnumbergenerator

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    backend.h \
    piechart.h \
    mainwindow.h \
    randomnumbergenerator.h
