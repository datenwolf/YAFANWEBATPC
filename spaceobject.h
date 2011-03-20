#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <QObject>
#include <QVector3D>
#include <GL/gl.h>
class SpaceObject : public QObject
{
    Q_OBJECT
public:
    explicit SpaceObject(QObject *parent = 0);
    qint32 objtype;
    qint32 flags;
    QVector3D position;
    QVector3D velocity;
    QVector3D rotation; //right hand rule rotation around axes.
    QVector3D rotvel;
    qint32 size;
    GLfloat* posfv(){ float f[]={position.x(),position.y(),position.z()}; return f; }
signals:

public slots:

};
QDataStream &operator<<(QDataStream &, const SpaceObject &);
QDataStream &operator>>(QDataStream &, SpaceObject &);
#endif // SPACEOBJECT_H
