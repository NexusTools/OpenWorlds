#include "openworldslauncher.h"
#include <QApplication>
#include <QDebug>
#include <QDir>

#include "path.h"

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
        sPath = QString::fromLocal8Bit(path).split(PATH_SEP);

#ifdef Q_OS_UNIX
    foreach(QString p, QStringList() << "/usr/bin" << "/bin" << "/local/bin" << "/local/usr/bin" << "/opt/bin" << "/opt/usr/bin") {
        if(!sPath.contains(p))
            sPath << p;
    }
#endif

    QStringList bases;
    {
        QString base = QDir::toNativeSeparators(QDir("..").absolutePath());
        if(!base.endsWith(QDir::separator()))
            base += QDir::separator();
        bases << base;
    }
    {
        QFileInfo myself(argv[0]);
        if(myself.exists()) {
            QString base = myself.dir().absolutePath();
            if(!base.endsWith(QDir::separator()))
                base += QDir::separator();
            bases << base;

            base = QFileInfo(QDir(base), "../..").dir().absolutePath();
            if(!base.endsWith(QDir::separator()))
                base += QDir::separator();
            bases << base;
        }
    }
    qDebug() << bases;

    foreach(QString base, bases)
        sPath << base + QDir::toNativeSeparators("extern/MoeGameEngine/client" RELEASE_DIR);
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
        lPath = QString::fromLocal8Bit(path).split(PATH_SEP);

    foreach(QString p, sPath) {
        if(!lPath.contains(p))
            lPath << p;
    }
#else
#define lPath sPath
#endif
    foreach(QString base, bases) {
        lPath << base + QDir::toNativeSeparators("extern/MoeGameEngine/extern/GenericUI/core" RELEASE_DIR);
        lPath << base + QDir::toNativeSeparators("extern/MoeGameEngine/extern/InputManager" RELEASE_DIR);
        lPath << base + QDir::toNativeSeparators("extern/MoeGameEngine/extern/ModularCore" RELEASE_DIR);
        lPath << base + QDir::toNativeSeparators("extern/MoeGameEngine/extern/NexusComm" RELEASE_DIR);
        lPath << base + QDir::toNativeSeparators("extern/MoeGameEngine/lib" RELEASE_DIR);
        lPath << base + QDir::toNativeSeparators("module" RELEASE_DIR);
    }

    qDebug() << "Using lib search path" << lPath;
    QDir::setSearchPaths("lib", lPath);


    OpenWorldsLauncher w;
    w.show();
    
    return a.exec();
}
