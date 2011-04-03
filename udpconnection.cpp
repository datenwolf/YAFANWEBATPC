#include "udpconnection.h"

UdpConnection::UdpConnection(int mode,Connection *parent):
        Connection(mode,parent), mode(mode)
{
    udpSocket = new QUdpSocket(this);
    switch(mode){
    case CONNECTION_MODE_SERVER:
        udpSocket->bind(QHostAddress::LocalHost, BASEPORT);
        break;
    case CONNECTION_MODE_CLIENT:
        udpSocket->bind(QHostAddress::LocalHost, BASEPORT+1);
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
    QString tmp(datagram.split(':').at(0));
    if(0==tmp.compare("DISCONNECT")){
        udpSocket->close();
        emit serverDisconnected();
    }else if(0==tmp.compare("MSG")){
        emit messageFromServer(datagram.mid(4));
    }
}




void UdpConnection::sparse(QByteArray datagram,QHostAddress sender){
    QString tmp(datagram.split(':').at(0));
    qDebug()<<tmp;
    if(0==tmp.compare("DISCONNECT")){
        emit clientDisconnection(sender.toString());
    }else if(0==tmp.compare("MSG")){
        emit messageFromClient(datagram.mid(4),sender.toString());
    }else if(0==tmp.compare("LOGIN")){
        emit clientLogIn(sender.toString());
    }
}


//client
void UdpConnection::logInToServer(QString server){
    udpSocket->connectToHost((const QString)server, BASEPORT,QUdpSocket::ReadWrite);
    udpSocket->write(QByteArray("LOGIN"));
}

void UdpConnection::sendToServer(QByteArray message){
    udpSocket->write(message.prepend("MSG:"));
}

void UdpConnection::disconnectFromServer(){
    udpSocket->write(QByteArray("DISCONNECT"));
}



//server
void UdpConnection::sendToClient(QByteArray message,QString client){
    udpSocket->writeDatagram ( message.prepend("MSG:"), QHostAddress(client), BASEPORT+1);
}

void UdpConnection::disconnectClient(QString client){
    udpSocket->writeDatagram (QByteArray("DISCONNECT"), QHostAddress(client), BASEPORT+1);
}
