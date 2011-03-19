#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

public slots:
    void messageFromClient(QDataStream& message,QString client){}
    void clientLogIn(QString client){}
    void clientDisconnection(QString client){ qDebug()<<"Client"<<client<<"disconnected"; emit disconnectClient(client);}
signals:
    void sendToClient(QDataStream& message,QString client);
    void disconnectClient(QString client);


};

#endif // SERVER_H
