#include "DepoPro.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <Qsettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DepoPro w;
    w.show();
    return a.exec();
}