#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

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
    void messageFromServer(QString message);//client
    void serverDisconnected();
    void messageFromClient(QString message,QString client);//server
    void clientLogIn(QString client);
    void clientDisconnection(QString client);
public slots:
    void logInToServer(QString server);//client
    void sendToServer(QString message);
    void disconnectFromServer();
    void sendToClient(QString message,QString client);//server
    void disconnectClient(QString client);

};

#endif // CONNECTION_H
