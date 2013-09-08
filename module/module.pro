#-------------------------------------------------
#
# Project created by QtCreator 2013-08-14T11:39:01
#
#-------------------------------------------------

QT       -= gui

TARGET = OpenWorlds
TEMPLATE = lib

DEFINES += MODULE_LIBRARY

SOURCES += openworlds.cpp

HEADERS += \
    openworlds.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extern/MoeGameEngine/lib/release/ -lMoeGameEngine0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extern/MoeGameEngine/lib/debug/ -lMoeGameEngine0
else:unix: LIBS += -L$$OUT_PWD/../extern/MoeGameEngine/lib/ -lMoeGameEngine

INCLUDEPATH += $$PWD/../extern/MoeGameEngine/lib
DEPENDPATH += $$PWD/../extern/MoeGameEngine/lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extern/MoeGameEngine/extern/ModularCore/release/ -lModularCore0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extern/MoeGameEngine/extern/ModularCore/debug/ -lModularCore0
else:unix: LIBS += -L$$OUT_PWD/../extern/MoeGameEngine/extern/ModularCore/ -lModularCore

INCLUDEPATH += $$PWD/../extern/MoeGameEngine/extern/ModularCore
DEPENDPATH += $$PWD/../extern/MoeGameEngine/extern/ModularCore

include($$PWD/../extern/MoeGameEngine/extern/GitProjectVersionQt/version.pri)
include($$PWD/../data/data.pri)
