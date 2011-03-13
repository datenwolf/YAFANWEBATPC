#include "objverttag.h"
#include <QStringList>

ObjVertTag::ObjVertTag()
{
}
bool ObjVertTag::parse(const QString& line){
    QStringList splitline=line.split(" ");
    float w=0.0f;
    bool ok=true;
    if(splitline.count()>4){
        ok=false;
        w=splitline[4].toFloat(&ok);
        if(!ok)
            w=0.0f;
    }
    ok=false;
    bool ok2=false;
    bool ok3=false;
    bool ok4=false;
    verts.append(QVector4D(splitline[1].toFloat(&ok2),splitline[2].toFloat(&ok3),splitline[3].toFloat(&ok4),w));
    return (ok&&ok2&&ok3&&ok4);
}
