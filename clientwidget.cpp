#include "clientwidget.h"

ClientWidget::ClientWidget(QGLWidget *parent)
    : QGLWidget(parent)
{
    qDebug()<<"widget init";
}

ClientWidget::~ClientWidget()
{
    qDebug()<<"widget destruct";
}

void ClientWidget::initializeGL()
{
    qDebug()<<"gl init";
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    qDebug()<<"gl init done";
}

void ClientWidget::resizeGL(int w, int h)
{
    qDebug()<<"gl resize";
    glViewport(0, 0, (GLint)w, (GLint)h);
    glFrustum(0,1,1,0,0,1);
    qDebug()<<"gl resize done";
}

void ClientWidget::paintGL()
{
    qDebug()<<"gl paint start";
    glBegin(GL_QUADS);
    qDebug()<<"glbegin quads success";
    qDebug()<<"vert1(";
    glVertex3f(0,0,0);
    qDebug()<<");vert2(";
    glVertex3f(1,1,0);
    qDebug()<<")";
    qDebug()<<"glend now";
    glEnd();
    qDebug()<<"gl paint end";
}
