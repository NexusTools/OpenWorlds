#include "openworldslauncher.h"
#include "ui_openworldslauncher.h"

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
    ui->version->setText(qApp->applicationVersion());

    QProcessEnvironment procEnv = QProcessEnvironment::systemEnvironment();
#ifdef Q_OS_UNIX
    procEnv.insert(
            #ifdef Q_OS_MAC
                "DYLD_FALLBACK_LIBRARY_PATH"
            #else
                "LD_LIBRARY_PATH"
            #endif
                , QDir::searchPaths("lib").join(':'));
    procEnv.insert("PATH", QDir::searchPaths("bin").join(':'));
#else
    procEnv.insert("PATH", QDir::searchPaths("lib").join(':'));
#endif
    qDebug() << procEnv.toStringList();

    _process.setProcessEnvironment(procEnv);
    connect(ui->launch, SIGNAL(clicked()), this, SLOT(launch()));
    connect(&_process, SIGNAL(finished(int)), this, SLOT(show()));
    connect(&_process, SIGNAL(started()), this, SLOT(hide()));

    connect(&_process, SIGNAL(readyReadStandardOutput()), this, SLOT(dumpStdOut()));
    connect(&_process, SIGNAL(readyReadStandardError()), this, SLOT(dumpErrOut()));
}

OpenWorldsLauncher::~OpenWorldsLauncher()
{
    delete ui;
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

    _process.start(moeLauncher.absoluteFilePath(), QStringList() << "--content" << openWorldsContent.absoluteFilePath());
}

void OpenWorldsLauncher::dumpStdOut() {
    qWarning() << _process.readAllStandardOutput();

}

void OpenWorldsLauncher::dumpErrOut() {
    qWarning() << _process.readAllStandardError();
}
