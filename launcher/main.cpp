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
    sPath << QDir("..").absolutePath() + "/module";

    qDebug() << "Using bin search path" << sPath;

    QDir::setSearchPaths("bin", sPath);


    OpenWorldsLauncher w;
    w.show();
    
    return a.exec();
}
