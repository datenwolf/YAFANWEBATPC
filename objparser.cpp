#include "objparser.h"
#include "objverttag.h"
#include <QStringList>

ObjParser::ObjParser(QFile& objfile) :
    objfile(objfile)
{
    ObjVertTag* v=new ObjVertTag;
    parser[v->tag()]=v;

    if (!objfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(objfile.readAll());
    while (!in.atEnd()) {
        QString line = in.readLine();
        parser[line.split(" ")[0]]->parse(line);
    }
}
