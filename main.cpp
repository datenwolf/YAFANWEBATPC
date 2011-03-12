#include <QtGui/QApplication>
#include "clientwidget.h"
#include <QDebug>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    qDebug()<<"main init";
    QApplication a(argc, argv);
    qDebug()<<"qapp"<<qApp->arguments().join(",").append("   LANG:").append(QLocale::system().name());
    QTranslator translator;
    translator.load(QLocale::system().name());
    a.installTranslator(&translator);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    ClientWidget w;
    qDebug()<<"widget created";
    w.showFullScreen();
    qDebug()<<"widget shown";


    return a.exec();
}
