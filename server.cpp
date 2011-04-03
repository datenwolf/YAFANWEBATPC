#include "server.h"
#include <qtimer.h>
#include <QVector3D>
#include <QDebug>
#include "global_defines.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(simulate()));
    timer->start(100);
}

void Server::simulate(){
    qDebug()<<ENCAPS(tr("serverside simulation"));
    QHashIterator<QString, QList<SpaceObject> > i(spaceObjects);
    while (i.hasNext()) {
        i.next();
        bool send=false;
        QByteArray qba;
        QDataStream stream(&qba,QIODevice::WriteOnly);
        stream << QString("SIMULATION_UPDATE_DATA");
        stream << i.value().size();
        for (int j = 0; j < i.value().size(); ++j) {
            stream << j;
            spaceObjects[i.key()][j].position+=i.value().at(j).velocity;
            spaceObjects[i.key()][j].rotation+=i.value().at(j).rotvel;
            send=true;
            stream << i.value().at(j);
        }
        emit sendToClient(qba,i.key());
    }
}
void Server::messageFromClient(QByteArray message,QString client){
    qDebug()<<ENCAPS(tr("[server] incoming"))<<message.toBase64()<<ENCAPS(tr("from"))<<client;
    QString header;
    QDataStream stream(message);
    stream >> header;
    qDebug()<<header;
    if(0==header.compare("SET_VELOCITY")){
        qDebug()<<ENCAPS(tr("Got velocity data!"));
        int i;
        stream >> i;
        stream >> spaceObjects[client][i].velocity;
    }
}
void Server::clientLogIn(QString client){
    qDebug()<<"Client"<<client<<"connected";
    QList<SpaceObject> l;
    l.append(SpaceObject());
    spaceObjects[client]=l;
}
void Server::clientDisconnection(QString client){
    qDebug()<<"Client"<<client<<"disconnected";
    spaceObjects.remove(client);
    emit disconnectClient(client);
}
