#include "openworldslauncher.h"
#include <QApplication>
#include <QDebug>
#include <QDir>

#include <project-version.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("OpenWorldsLauncher");
    a.setOrganizationName("NexusTools");
    a.setApplicationVersion(VERSION);

    QStringList sPath;
    char* path = getenv("PATH");
    if(path)
        sPath = QString::fromLocal8Bit(path).split(':');

    foreach(QString p, QStringList() << "/usr/bin" << "/bin" << "/local/bin" << "/local/usr/bin" << "/opt/bin" << "/opt/usr/bin") {
        if(!sPath.contains(p))
            sPath << p;
    }

    sPath << QDir("..").absolutePath() + "/extern/MoeGameEngine/client";
    qDebug() << "Using bin search path" << sPath;
    QDir::setSearchPaths("bin", sPath);

#ifdef Q_OS_UNIX
    QStringList lPath;
    path = getenv(
            #ifdef Q_OS_MAC
                "DYLD_FALLBACK_LIBRARY_PATH"
            #else
                "LD_LIBRARY_PATH"
            #endif
                );
    if(path)
        lPath = QString::fromLocal8Bit(path).split(':');

    foreach(QString p, sPath) {
        if(!lPath.contains(p))
            lPath << p;
    }
#else
#define lpath spath;
#endif

    lPath << QDir("..").absolutePath() + "/extern/MoeGameEngine/extern/GenericUI/core";
    lPath << QDir("..").absolutePath() + "/extern/MoeGameEngine/extern/InputManager";
    lPath << QDir("..").absolutePath() + "/extern/MoeGameEngine/extern/ModularCore";
    lPath << QDir("..").absolutePath() + "/extern/MoeGameEngine/extern/NexusComm";
    lPath << QDir("..").absolutePath() + "/extern/MoeGameEngine/lib";
    lPath << QDir("..").absolutePath() + "/module";
    qDebug() << "Using lib search path" << lPath;
    QDir::setSearchPaths("lib", lPath);


    OpenWorldsLauncher w;
    w.show();
    
    return a.exec();
}
