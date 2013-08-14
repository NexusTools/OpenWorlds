#ifndef OPENWORLDSLAUNCHER_H
#define OPENWORLDSLAUNCHER_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class OpenWorldsLauncher;
}

class OpenWorldsLauncher : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit OpenWorldsLauncher(QWidget *parent = 0);
    ~OpenWorldsLauncher();

public slots:
    void launch();

    void dumpErrOut();
    void dumpStdOut();
    
private:
    Ui::OpenWorldsLauncher *ui;
    QProcess _process;
};

#endif // OPENWORLDSLAUNCHER_H
