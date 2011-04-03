#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include "connection.h"
#include <QUdpSocket>
#include "global_defines.h"
#include <QApplication>

#define BASEPORT 40959
//base port number defined by following bash command:
//  echo yafanwebatpc | sha1sum | cut -d" " -f 1 | tr -d "[:alpha:]" | cut -c 1-5

class UdpConnection : public Connection
{
    Q_OBJECT
public:
    UdpConnection(int mode,Connection *parent = 0);
    int mode;
private:
    QUdpSocket* udpSocket;
    void cparse(QByteArray,QHostAddress);
    void sparse(QByteArray,QHostAddress);
signals:
    void messageFromServer(QByteArray message);//client
    void serverDisconnected();
    void messageFromClient(QByteArray message,QString client);//server
    void clientLogIn(QString client);
    void clientDisconnection(QString client);
public slots:
    void logInToServer(QString server);//client
    void sendToServer(QByteArray message);
    void disconnectFromServer();
    void sendToClient(QByteArray message,QString client);//server
    void disconnectClient(QString client);
    void readPendingDatagrams();
};

#endif // UDPCONNECTION_H
