#include "openworldslauncher.h"
#include "ui_openworldslauncher.h"
#include "path.h"

#include <QProcessEnvironment>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QDir>

OpenWorldsLauncher::OpenWorldsLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenWorldsLauncher)
{
    ui->setupUi(this);
    setWindowTitle(QString("OpenWorlds Launcher V%1").arg(qApp->applicationVersion()));
    ui->version->setText(QString("V%1").arg(qApp->applicationVersion()));
    ui->progressBar->hide();

    QProcessEnvironment procEnv = QProcessEnvironment::systemEnvironment();
#ifdef Q_OS_UNIX
    procEnv.insert(
            #ifdef Q_OS_MAC
                "DYLD_FALLBACK_LIBRARY_PATH"
            #else
                "LD_LIBRARY_PATH"
            #endif
                , QDir::searchPaths("lib").join(PATH_SEP));
    procEnv.insert("PATH", QDir::searchPaths("bin").join(PATH_SEP));
#else
    procEnv.insert("PATH", QDir::searchPaths("lib").join(PATH_SEP));
#endif
    qDebug() << procEnv.toStringList();

    _process.setProcessEnvironment(procEnv);
    connect(ui->launch, SIGNAL(clicked()), this, SLOT(launch()));
    connect(&_process, SIGNAL(finished(int)), this, SLOT(show()));
    connect(&_process, SIGNAL(started()), this, SLOT(hide()));

    connect(&_process, SIGNAL(readyReadStandardOutput()), this, SLOT(dumpStdOut()));
    connect(&_process, SIGNAL(readyReadStandardError()), this, SLOT(dumpErrOut()));
}

void OpenWorldsLauncher::launch() {
    QFileInfo moeLauncher(
            #ifdef Q_OS_UNIX
                "bin:MoeGameLauncher"
            #else
                "bin:MoeGameLauncher.exe"
            #endif
                );
    if(!moeLauncher.exists()) {
        QMessageBox::critical(this, "Missing MoeGameEngine", QString("Unable to find the install directory for %1, you may have to reinstall it").arg(moeLauncher.fileName()));
        return;
    }

    QFileInfo openWorldsContent(
            #ifdef Q_OS_UNIX
                "lib:libOpenWorlds.so"
            #else
                "lib:OpenWorlds0.dll"
            #endif
                );
    if(!openWorldsContent.exists()) {
        QMessageBox::critical(this, "Missing game content", QString("Unable to find the install directory for %1, you may have to reinstall it").arg(openWorldsContent.fileName()));
        return;
    }

    QStringList contentLookupPaths;
    contentLookupPaths << "./packages";
    contentLookupPaths << QDir::currentPath();

    _process.setWorkingDirectory(moeLauncher.dir().absolutePath());
    _process.start(moeLauncher.absoluteFilePath(), QStringList() << "--content" << openWorldsContent.absoluteFilePath() << "--content-lookup-path" << contentLookupPaths.join(':'));
}

void OpenWorldsLauncher::dumpStdOut() {
    QByteArray msg = _process.readAllStandardOutput();

    fwrite(msg.data(), 1, msg.size(), stdout);
    fflush(stdout);
}

void OpenWorldsLauncher::dumpErrOut() {
    QByteArray msg = _process.readAllStandardError();

    fwrite(msg.data(), 1, msg.size(), stderr);
    fflush(stderr);
}

OpenWorldsLauncher::~OpenWorldsLauncher()
{
    delete ui;
}
