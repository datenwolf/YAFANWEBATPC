#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QtGui/QWidget>
#include <QGLWidget>
#include <QDebug>
#include <QPainterPath>
#include <QList>
#include <QPolygonF>
#include <QLabel>
#include <QPixmap>
#include <QLCDNumber>
#include <QDataStream>
#include <QBitmap>
#include "spaceobject.h"
#include "global_defines.h"
#include "glspaceobject.h"
#ifdef QT_TO_TEXTURE_FLIP
#define QT_TO_TEXTURE_ROTATION 0
#else
#define QT_TO_TEXTURE_ROTATION 1
#endif


class ClientWidget : public QGLWidget
{
    Q_OBJECT

public:
    ClientWidget(QGLWidget *parent = 0);
    ~ClientWidget();

protected:

     void initializeGL();
     void resizeGL(int w, int h);
     void paintGL();
     void drawHUD();
private:
     SpaceObject me;
     int frames; float ftmp;
     QLabel fpslabel;
     QPixmap fpspix;
     GLuint fpstex;
     QLCDNumber clocklcd;
     QPixmap clockpix;
     GLuint clocktex;
     QImage hud;
     GLuint hudtex;
     QBitmap emptybm;
     GLSpaceObject teapot;
     QList<QVector3D> stars;
protected slots:
     void animate();
     void fpscalc();
     void keyReleaseEvent(QKeyEvent *);
     void messageFromServer(QDataStream& message){}
     void serverDisconnected();
signals:
     void logInToServer(QString server);
     void sendToServer(QDataStream& message);
     void disconnectFromServer();

};

#endif // CLIENTWIDGET_H
