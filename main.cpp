#include <QtGui/QApplication>
#include "clientwidget.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug()<<"main init";
    QApplication a(argc, argv);
    qDebug()<<"qapp";
    ClientWidget w;
    qDebug()<<"widget created";
    w.show();
    qDebug()<<"widget shown";


    return a.exec();
}
