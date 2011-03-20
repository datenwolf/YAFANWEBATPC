#include "ctmspaceobject.h"

CTMSpaceObject::CTMSpaceObject()
{
}

void CTMSpaceObject::render(){
    glVertex3fv(vertices);
}
void CTMSpaceObject::load(QString fn){
    filename=fn;
    ctm.Load(filename.toUtf8().data());
    vertCount = ctm.GetInteger(CTM_VERTEX_COUNT);
    vertices =(CTMfloat*) ctm.GetFloatArray(CTM_VERTICES);
    triCount = ctm.GetInteger(CTM_TRIANGLE_COUNT);
    indices =(CTMuint*) ctm.GetIntegerArray(CTM_INDICES);
}

QDataStream &operator<<(QDataStream& s, const CTMSpaceObject& o){
    s << "%CTMSPACEOBJECT%";
    s << o.objtype;
    s << o.flags;
    s << o.position;
    s << o.velocity;
    s << o.rotation; //right hand rule rotation around axes.
    s << o.rotvel;
    s << o.size;
    s << o.filename;
    return s;
}

QDataStream &operator>>(QDataStream& s, CTMSpaceObject& o){
    char* n;
    s >> n;
    if(QString("%CTMSPACEOBJECT%").compare(n)==0){
        s >> o.objtype;
        s >> o.flags;
        s >> o.position;
        s >> o.velocity;
        s >> o.rotation;
        s >> o.rotvel;
        s >> o.size;
        s >> o.filename;
    }
    return s;
}
