#include "spaceobject.h"

SpaceObject::SpaceObject(QObject *parent)
{
}
QDataStream &operator<<(QDataStream& s, const SpaceObject& o){
    s << "%SPACEOBJECT%";
    s << o.objtype;
    s << o.flags;
    s << o.position;
    s << o.velocity;
    s << o.rotation; //right hand rule rotation around axes.
    s << o.rotvel;
    s << o.size;
    return s;
}

QDataStream &operator>>(QDataStream& s, SpaceObject& o){
    char* n;
    s >> n;
    if(QString("%SPACEOBJECT%").compare(n)==0){
        s >> o.objtype;
        s >> o.flags;
        s >> o.position;
        s >> o.velocity;
        s >> o.rotation;
        s >> o.rotvel;
        s >> o.size;
    }
    return s;
}
