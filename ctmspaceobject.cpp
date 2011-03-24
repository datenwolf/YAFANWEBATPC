#include "ctmspaceobject.h"
#include <QDebug>
CTMSpaceObject::CTMSpaceObject()
{
}

void CTMSpaceObject::render(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES,  triCount*3, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}
void CTMSpaceObject::load(QString fn){
    filename=fn;
    ctm.Load(filename.toUtf8().data());
    vertCount = ctm.GetInteger(CTM_VERTEX_COUNT);
    vertices =(CTMfloat*) ctm.GetFloatArray(CTM_VERTICES);
    triCount = ctm.GetInteger(CTM_TRIANGLE_COUNT);
    indices =(CTMuint*) ctm.GetIntegerArray(CTM_INDICES);
    qDebug()<<"CTM:"<<fn<<"vertCount:"<<vertCount<<"triCount:"<<triCount;
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
