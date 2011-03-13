#ifndef OBJVERTTAG_H
#define OBJVERTTAG_H
#include "objtag.h"
#include <QVector4D>
class ObjVertTag : public ObjTag
{
public:
    ObjVertTag();
    const QString tag() { return QString("v"); }
    bool parse(const QString& line);
private:
    QList<QVector4D> verts;

};

#endif // OBJVERTTAG_H
