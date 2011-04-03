#include <QtGui/QApplication>
#include "clientwidget.h"
#include <QDebug>
#include <QTextCodec>
#include <QTranslator>
#include "udpconnection.h"
#include "server.h"
int main(int argc, char *argv[])
{
    qDebug()<<"main init";
    QApplication a(argc, argv);
    qDebug()<<"qapp"<<a.arguments().join(",")<<"   LANG: "<<QLocale::system().name();
    QTranslator translator;
    translator.load(QLocale::system().name());
    a.installTranslator(&translator);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));


    if(a.arguments().contains("-s")){
        qDebug()<<"setting up server";
        UdpConnection c(CONNECTION_MODE_SERVER);
        Server s;
        QObject::connect(&c,SIGNAL(messageFromClient(QByteArray,QString)),&s,SLOT(messageFromClient(QByteArray,QString)));
        QObject::connect(&c,SIGNAL(clientLogIn(QString)),&s,SLOT(clientLogIn(QString)));
        QObject::connect(&c,SIGNAL(clientDisconnection(QString)),&s,SLOT(clientDisconnection(QString)));
        QObject::connect(&s,SIGNAL(sendToClient(QByteArray,QString)),&c,SLOT(sendToClient(QByteArray,QString)));
        QObject::connect(&s,SIGNAL(disconnectClient(QString)),&c,SLOT(disconnectClient(QString)));
        qDebug()<<"return qapp.exec() main loop, bye.";
        return a.exec();
    }else{
        qDebug()<<"setting up client";
        ClientWidget w;
        qDebug()<<"widget created";
        UdpConnection c(CONNECTION_MODE_CLIENT);
        QObject::connect(&w,SIGNAL(logInToServer(QString)),&c,SLOT(logInToServer(QString)));
        QObject::connect(&w,SIGNAL(sendToServer(QByteArray)),&c,SLOT(sendToServer(QByteArray)));
        QObject::connect(&w,SIGNAL(disconnectFromServer()),&c,SLOT(disconnectFromServer()));
        QObject::connect(&c,SIGNAL(messageFromServer(QByteArray)),&w,SLOT(messageFromServer(QByteArray)));
        QObject::connect(&c,SIGNAL(serverDisconnected()),&w,SLOT(serverDisconnected()));
        w.showFullScreen();
        qDebug()<<"return qapp.exec() main loop, bye.";
        return a.exec();
    }
}
