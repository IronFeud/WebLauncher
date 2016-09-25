#include "mainwindow.h"
#include <QApplication>
#include "qmcl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMCl mClass;

    return a.exec();
}
