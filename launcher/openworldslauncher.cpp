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
    procEnv.insert("LD_LIBRARY_PATH", QDir::searchPaths("lib").join(':'));
    procEnv.insert("PATH", QDir::searchPaths("bin").join(':'));
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
    QFileInfo moeLauncher("bin:MoeGameLauncher");
    if(!moeLauncher.exists()) {
        QMessageBox::critical(this, "Can't find MoeGameLauncher", "Unable to find the install directory for MoeGameLauncher, you may have to reinstall it");
        return;
    }

    QFileInfo openWorldsContent("lib:libOpenWorlds.so");
    if(!openWorldsContent.exists()) {
        QMessageBox::critical(this, "Can't find libOpenWorlds.so", "Unable to find the install directory for libOpenWorlds.so, you may have to reinstall it");
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
