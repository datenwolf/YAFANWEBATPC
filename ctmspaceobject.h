#ifndef CTMSPACEOBJECT_H
#define CTMSPACEOBJECT_H
#include "glspaceobject.h"
#include <openctm.h>
class CTMSpaceObject : public GLSpaceObject
{
public:
    CTMSpaceObject();
    void load(QString fn,float s=1);
    void render();
    QString filename;
    CTMuint vertCount, triCount, * indices;
    CTMfloat * vertices, *normals;
    CTMimporter ctm;
    void CalcNormals(float s=1);
};
QDataStream &operator<<(QDataStream &, const CTMSpaceObject &);
QDataStream &operator>>(QDataStream &, CTMSpaceObject &);
#endif // CTMSPACEOBJECT_H
