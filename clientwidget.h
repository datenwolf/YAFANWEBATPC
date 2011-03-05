#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QtGui/QWidget>
#include <QGLWidget>
#include <QDebug>

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

};

#endif // CLIENTWIDGET_H
