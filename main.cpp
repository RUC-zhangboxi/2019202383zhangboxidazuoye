//#include "mainwindow.h"
#include "startfrom.h"      //开始场景
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartFrom w;
    w.show();

    return a.exec();
}
