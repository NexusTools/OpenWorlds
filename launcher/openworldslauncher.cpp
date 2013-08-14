#include "openworldslauncher.h"
#include "ui_openworldslauncher.h"

#include <QMessageBox>
#include <QFileInfo>

OpenWorldsLauncher::OpenWorldsLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenWorldsLauncher)
{
    ui->setupUi(this);
    ui->version->setText(qApp->applicationVersion());

    connect(ui->launch, SIGNAL(clicked()), this, SLOT(launch()));
    connect(&_process, SIGNAL(finished(int)), this, SLOT(show()));
    connect(&_process, SIGNAL(started()), this, SLOT(hide()));
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

    QFileInfo openWorldsContent("bin:libOpenWorlds.so");
    if(!openWorldsContent.exists()) {
        QMessageBox::critical(this, "Can't find libOpenWorlds.so", "Unable to find the install directory for libOpenWorlds.so, you may have to reinstall it");
        return;
    }


    _process.start(moeLauncher.absoluteFilePath(), QStringList() << "--content" << openWorldsContent.absoluteFilePath());
}
