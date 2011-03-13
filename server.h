#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

public slots:
    void messageFromClient(QString message,QString client){}
    void clientLogIn(QString client){}
    void clientDisconnection(QString client){}
signals:
    void sendToClient(QString message,QString client);
    void disconnectClient(QString client);


};

#endif // SERVER_H
