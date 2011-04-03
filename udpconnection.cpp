#include "udpconnection.h"

UdpConnection::UdpConnection(int mode,Connection *parent):
        Connection(mode,parent), mode(mode)
{
    udpSocket = new QUdpSocket(this);
    switch(mode){
    case CONNECTION_MODE_SERVER:
        qDebug()<<"SERVER bind at"<<BASEPORT;
        if(!udpSocket->bind(BASEPORT)){
            qDebug()<<ENCAPS(tr("UdpConnection constructor: socket not bound."));
            qApp->exit();
        }
        break;

    case CONNECTION_MODE_CLIENT:
        qDebug()<<"CLIENT bind at"<<BASEPORT+1;
        if(!udpSocket->bind(BASEPORT+1)){
            qDebug()<<ENCAPS(tr("UdpConnection constructor: socket not bound."));
            qApp->exit();
        }
        break;

    default:
        qDebug()<<ENCAPS(tr("UdpConnection constructor: wrong mode: "))<<mode;
        qApp->exit();
        break;
    }

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void UdpConnection::readPendingDatagrams()
 {
     while (udpSocket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(udpSocket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         udpSocket->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);

         switch (mode){
         case CONNECTION_MODE_CLIENT:
             cparse(datagram,sender);
             break;

         case CONNECTION_MODE_SERVER:
             sparse(datagram,sender);
             break;
         }
     }
}


void UdpConnection::cparse(QByteArray datagram,QHostAddress sender){
    qDebug()<<"cparse"<<datagram.toBase64()<<sender;
    QString tmp(datagram.split(':').at(0));
    if( 0 == tmp.compare("DISCONNECT") ) {
        udpSocket->close();
        emit serverDisconnected();
    } else if( 0 == tmp.compare("MSG") ) {
        emit messageFromServer(datagram.mid(4));
    }
}




void UdpConnection::sparse(QByteArray datagram,QHostAddress sender){
    qDebug()<<"sparse"<<datagram.toBase64()<<sender;
    QString tmp(datagram.split(':').at(0));

    if( 0 == tmp.compare("DISCONNECT") ) {
        emit clientDisconnection(sender.toString());
    } else if( 0 == tmp.compare("MSG") ) {
        emit messageFromClient(datagram.mid(4),sender.toString());
    } else if( 0 == tmp.compare("LOGIN") ) {
        emit clientLogIn(sender.toString());
    }
}


//client
void UdpConnection::logInToServer(QString server){
    qDebug()<<"logInToServer"<<server;
    udpSocket->writeDatagram(QByteArray("LOGIN"), QHostAddress(server), BASEPORT);
}

void UdpConnection::sendToServer(QByteArray message, QString server){
    qDebug()<<"sendToServer"<<message.toBase64();
    udpSocket->writeDatagram(message.prepend("MSG:"), QHostAddress(server), BASEPORT);
}

void UdpConnection::disconnectFromServer(QString server){
    qDebug()<<"disconnectFromServer";
    udpSocket->writeDatagram(QByteArray("DISCONNECT"), QHostAddress(server), BASEPORT);
}



//server
void UdpConnection::sendToClient(QByteArray message,QString client){
    qDebug()<<"sendToClient"<<message.toBase64()<<client;
    udpSocket->writeDatagram ( message.prepend("MSG:"), QHostAddress(client), BASEPORT+1);
}

void UdpConnection::disconnectClient(QString client){
    qDebug()<<"disconnectClient"<<client;
    udpSocket->writeDatagram (QByteArray("DISCONNECT"), QHostAddress(client), BASEPORT+1);
}
