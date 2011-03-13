#ifndef LOOPBACKCONNECTION_H
#define LOOPBACKCONNECTION_H
#include "connection.h"
class LoopbackConnection : public Connection
{
    Q_OBJECT
public:
    LoopbackConnection(int mode,Connection *parent = 0);
    int mode;

signals:
    void messageFromServer(QDataStream& message);//client
    void serverDisconnected();
    void messageFromClient(QDataStream& message,QString client);//server
    void clientLogIn(QString client);
    void clientDisconnection(QString client);
public slots:
    void logInToServer(QString server);//client
    void sendToServer(QDataStream& message);
    void disconnectFromServer();
    void sendToClient(QDataStream& message,QString client);//server
    void disconnectClient(QString client);

};

#endif // LOOPBACKCONNECTION_H
