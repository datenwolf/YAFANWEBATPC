#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QDebug>
#include "spaceobject.h"
#include <QList>
#include <QHash>

class Server : public QThread
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void run();
    QHash<QString,QList<SpaceObject> > spaceObjects;

public slots:
    void messageFromClient(QByteArray message,QString client);
    void clientLogIn(QString client){}
    void clientDisconnection(QString client){ qDebug()<<"Client"<<client<<"disconnected"; exit(); emit disconnectClient(client);}
    void simulate();
signals:
    void sendToClient(QByteArray message,QString client);
    void disconnectClient(QString client);


};

#endif // SERVER_H
