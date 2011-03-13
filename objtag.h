#ifndef OBJTAG_H
#define OBJTAG_H
#include <QString>
#include "global_defines.h"
#include <QDebug>
#include <QCoreApplication>
class ObjTag
{
public:
    ObjTag(){}
    virtual const QString tag() { return QString(""); }
    virtual bool parse(const QString& line) { qDebug()<<ENCAPS(QCoreApplication::translate("ObjTag","empty objTag parse stub."))<<line; return false; }
};

#endif // OBJTAG_H
