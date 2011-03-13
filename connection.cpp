#include "connection.h"

Connection::Connection(int mode,QObject *parent) :
    QObject(parent), mode(mode)
{
}
