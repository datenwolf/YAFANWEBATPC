#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QDataStream>

#define CONNECTION_MODE_SERVER 0
#define CONNECTION_MODE_CLIENT 1
#define CONNECTION_MODE_BOTH 2

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(int mode,QObject *parent = 0);
    int mode;

signals:
    void messageFromServer(QDataStream& message);//client
    void serverDisconnected();
    void messageFromClient(QDataStream& message,QString client);//server
    void clientLogIn(QString client);
    void clientDisconnection(QString client);
public slots:
    virtual void logInToServer(QString server){}//client
    virtual void sendToServer(QDataStream& message){}
    virtual void disconnectFromServer(){}
    virtual void sendToClient(QDataStream& message,QString client){}//server
    virtual void disconnectClient(QString client){}

};

#endif // CONNECTION_H
