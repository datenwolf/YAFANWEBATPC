#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include "spaceobject.h"
#include <QList>
#include <QHash>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    QHash<QString,QList<SpaceObject> > spaceObjects;

public slots:
    void messageFromClient(QByteArray message,QString client);
    void clientLogIn(QString client);
    void clientDisconnection(QString client);
    void simulate();
signals:
    void sendToClient(QByteArray message,QString client);
    void disconnectClient(QString client);


};

#endif // SERVER_H
