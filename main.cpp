#include <QtGui/QApplication>
#include "clientwidget.h"
#include <QDebug>
#include <QTextCodec>
#include <QTranslator>
#if 1
#include "loopbackconnection.h"
#include "server.h"
#endif
int main(int argc, char *argv[])
{
    qDebug()<<"main init";
    QApplication a(argc, argv);
    qDebug()<<"qapp"<<a.arguments().join(",")<<"   LANG: "<<QLocale::system().name();
    QTranslator translator;
    translator.load(QLocale::system().name());
    a.installTranslator(&translator);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    ClientWidget w;
    qDebug()<<"widget created";
    w.showFullScreen();
    qDebug()<<"widget shown";


    qDebug()<<"setting up loopback connection";
    LoopbackConnection c(CONNECTION_MODE_BOTH);
    Server s;
    QObject::connect(&w,SIGNAL(logInToServer(QString)),&c,SLOT(logInToServer(QString)));
    QObject::connect(&w,SIGNAL(sendToServer(QDataStream&)),&c,SLOT(sendToServer(QDataStream&)));
    QObject::connect(&w,SIGNAL(disconnectFromServer()),&c,SLOT(disconnectFromServer()));

    QObject::connect(&s,SIGNAL(sendToClient(QDataStream&,QString)),&c,SLOT(sendToClient(QDataStream&,QString)));
    QObject::connect(&s,SIGNAL(disconnectClient(QString)),&c,SLOT(disconnectClient(QString)));

    QObject::connect(&c,SIGNAL(messageFromServer(QDataStream&)),&w,SLOT(messageFromServer(QDataStream&)));
    QObject::connect(&c,SIGNAL(serverDisconnected()),&w,SLOT(serverDisconnected()));

    QObject::connect(&c,SIGNAL(messageFromClient(QDataStream&,QString)),&s,SLOT(messageFromClient(QDataStream&,QString)));
    QObject::connect(&c,SIGNAL(clientLogIn(QString)),&s,SLOT(clientLogIn(QString)));
    QObject::connect(&c,SIGNAL(clientDisconnection(QString)),&s,SLOT(clientDisconnection(QString)));
    qDebug()<<"done";

    qDebug()<<"return qapp.exec() main loop, bye.";
    return a.exec();
}
