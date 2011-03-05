#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <QObject>
#include <QVector3D>
class SpaceObject : public QObject
{
    Q_OBJECT
public:
    explicit SpaceObject(QObject *parent = 0);
    qint32 objtype;
    qint32 flags;
    QVector3D position;
    QVector3D rotation; //right hand rule rotation around axes.

signals:

public slots:

};
QDataStream &operator<<(QDataStream &, const SpaceObject &);
QDataStream &operator>>(QDataStream &, SpaceObject &);
#endif // SPACEOBJECT_H
