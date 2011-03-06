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
     int frames;
     QList<QPointF> led1circle;
     QList<QPointF> radar;
     QList<QPointF> halfradar;
     QPointF radar_tl;
     QPointF radar_tr;
     bool led1ON;
     QLabel fpslabel;
     QPixmap fpspix;
     GLuint fpstex;
protected slots:
     void animate();
     void fpscalc();
     void keyReleaseEvent(QKeyEvent *);

};

#endif // CLIENTWIDGET_H
