#ifndef CTMSPACEOBJECT_H
#define CTMSPACEOBJECT_H
#include "glspaceobject.h"
#include <openctm.h>
class CTMSpaceObject : public GLSpaceObject
{
    Q_OBJECT
public:
    CTMSpaceObject();
    void load(QString fn);
    void render();
    QString filename;
    CTMuint vertCount, triCount, * indices;
    CTMfloat * vertices, *normals;
    CTMimporter ctm;
};
QDataStream &operator<<(QDataStream &, const CTMSpaceObject &);
QDataStream &operator>>(QDataStream &, CTMSpaceObject &);
#endif // CTMSPACEOBJECT_H
