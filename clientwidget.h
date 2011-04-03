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
#include "ctmspaceobject.h"
#include <FTGL/ftgl.h>
#include <QGLShaderProgram>
#include <QGLShader>
#ifdef QT_TO_TEXTURE_FLIP
#define QT_TO_TEXTURE_ROTATION 0
#else
#define QT_TO_TEXTURE_ROTATION 1
#endif
#define CWRF_BOTTOM 0
#define CWRF_TOP 1
#define CWRF_LEFT 0
#define CWRF_RIGHT 1
#define CWRF_CENTER 2

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
     void renderFont(FTPixmapFont* f, QString s, float x,float y,int lr,int tb);
private:
     QGLShaderProgram lightingprogram;
     SpaceObject me;
     int frames; float ftmp;
     QString fps;
     QString clock;
     QImage hud;
     GLuint hudtex;
     GLSpaceObject teapot;
     CTMSpaceObject bunny;
     FTPixmapFont* font;
protected slots:
     void animate();
     void fpscalc();
     void keyReleaseEvent(QKeyEvent *);
     void messageFromServer(QByteArray message);
     void serverDisconnected();
signals:
     void logInToServer(QString server);
     void sendToServer(QByteArray message);
     void disconnectFromServer();

};

#endif // CLIENTWIDGET_H
