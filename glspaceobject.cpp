#include "glspaceobject.h"
#include "GL/glut.h"
#include "global_defines.h"

GLSpaceObject::GLSpaceObject()
{
}

void GLSpaceObject::render(){
    glFrontFace(GL_CW);
    glutSolidTeapot(I2F(size));
    glFrontFace(GL_CCW);
}


QDataStream &operator<<(QDataStream& s, const GLSpaceObject& o){
    s << "%SPACEOBJECT%";
    s << o.objtype;
    s << o.flags;
    s << o.position;
    s << o.velocity;
    s << o.rotation;
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
