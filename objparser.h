#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <QObject>
#include <QFile>
#include "objtag.h"

class ObjParser
{
public:
    explicit ObjParser(QFile& objfile);
private:
    QFile& objfile;
    QMap<QString,ObjTag*> parser;
};

#endif // OBJPARSER_H
