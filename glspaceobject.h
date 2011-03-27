#ifndef GLSPACEOBJECT_H
#define GLSPACEOBJECT_H
#include "spaceobject.h"
class GLSpaceObject : public SpaceObject
{
public:
    GLSpaceObject();
    void render();
};
QDataStream &operator<<(QDataStream &, const GLSpaceObject &);
QDataStream &operator>>(QDataStream &, GLSpaceObject &);

#endif // GLSPACEOBJECT_H
