#-------------------------------------------------
#
# Project created by QtCreator 2013-08-14T11:37:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = launcher
TEMPLATE = app

CONFIG(debug, debug|release): DEFINES += DEBUG_BUILD

SOURCES += main.cpp\
        openworldslauncher.cpp

HEADERS  += openworldslauncher.h \
    path.h

FORMS    += openworldslauncher.ui

include($$PWD/../extern/MoeGameEngine/extern/GitProjectVersionQt/version.pri)

RESOURCES += \
    data.qrc

DEPENDPATH += $$PWD/../extern/MoeGameEngine/client/
