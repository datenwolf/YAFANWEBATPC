#include "clientwidget.h"
#include <QTimer>

ClientWidget::ClientWidget(QGLWidget *parent)
    : QGLWidget(parent)
{
    qDebug()<<"widget init";
    x=0.0;xdir=false;
}

ClientWidget::~ClientWidget()
{
    qDebug()<<"widget destruct";
}

void ClientWidget::initializeGL()
{
    qDebug()<<"gl init";
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);							// The Type Of Depth Test To Do
    glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(10);
    qDebug()<<"gl init done";
}

void ClientWidget::resizeGL(int w, int h)
{
    qDebug()<<"gl resize";
    glViewport(0, 0, (GLint)w, (GLint)h);
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
    qDebug()<<"gl resize done";
}

void ClientWidget::paintGL()
{
    qDebug()<<"gl paint start";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();					// Reset The Current Modelview Matrix
    glBegin(GL_TRIANGLES);					// Begin Drawing Triangles
    glColor3f(1.0f-x,x,x);			// Set The Color To Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Move Up One Unit From Center (Top Point)
    glColor3f(x,1.0f-x,x);			// Set The Color To Green
    glVertex3f(-1.0f,-1.0f, 0.0f);			// Left And Down One Unit (Bottom Left)
    glColor3f(x,x,1.0f-x);			// Set The Color To Blue
    glVertex3f( 1.0f,-1.0f, 0.0f);			// Right And Down One Unit (Bottom Right)
    glEnd();						// Done Drawing A Triangle
    qDebug()<<"gl paint end";
}
void ClientWidget::animate()
{
    qDebug()<<"animate() start";
    if(xdir){
        x+=0.01f;
    }else{
        x-=0.02f;
    }
    if(x>=1.0f){
        xdir=!xdir;
        x=1.0f;
    }else if(x<=0.0f){
        xdir=!xdir;
        x=0.0f;
    }
    updateGL();
    qDebug()<<"animate() end";
}
