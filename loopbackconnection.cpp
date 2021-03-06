#include "loopbackconnection.h"

LoopbackConnection::LoopbackConnection(int mode,Connection *parent):
        Connection(mode,parent), mode(mode)
{
}

//client
void LoopbackConnection::logInToServer(QString server){
    emit clientLogIn("loop");
}

void LoopbackConnection::sendToServer(QByteArray message){
    emit messageFromClient(message,"loop");
}

void LoopbackConnection::disconnectFromServer(){
    emit clientDisconnection("loop");
}



//server
void LoopbackConnection::sendToClient(QByteArray message,QString client){
    emit messageFromServer(message);
}

void LoopbackConnection::disconnectClient(QString client){
    emit serverDisconnected();
}
