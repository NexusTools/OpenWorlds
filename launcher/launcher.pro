#-------------------------------------------------
#
# Project created by QtCreator 2013-08-14T11:37:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = launcher
TEMPLATE = app


SOURCES += main.cpp\
        openworldslauncher.cpp

HEADERS  += openworldslauncher.h \
    path.h

FORMS    += openworldslauncher.ui

include($$PWD/../extern/MoeGameEngine/extern/GitProjectVersionQt/version.pri)
