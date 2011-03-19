#include "glspaceobject.h"
#include "GL/glut.h"
#include "global_defines.h"

GLSpaceObject::GLSpaceObject()
{
}

void GLSpaceObject::render(){
    glutSolidTeapot(I2F(size));
}


QDataStream &operator<<(QDataStream& s, const GLSpaceObject& o){
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

QDataStream &operator>>(QDataStream& s, GLSpaceObject& o){
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
