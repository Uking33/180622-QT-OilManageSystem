#include "mainwindow.h"
#include "iniData.h"
#include "globalapplication.h"
#include <QProcess>

int main(int argc, char *argv[])
{    
    GlobalApplication a(argc, argv);
    //Data data;
    IniData ini;
    MainWindow w(&ini);
    w.show();
    int ret;
    a.connect(&a, SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    ret = a.exec();
    if(ret==1){
        QProcess::startDetached(qApp->applicationFilePath(),QStringList());
        return 0;
    }
    return ret;
}
