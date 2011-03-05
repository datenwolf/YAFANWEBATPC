#include "clientwidget.h"
#include <QTimer>

QList<QPolygonF> text2polylist(char* font, int size, QString str){
    QPainterPath path;
    path.addText(QPointF(0, 0), QFont(font, size), QString(str));
    return path.toSubpathPolygons();
}



ClientWidget::ClientWidget(QGLWidget *parent)
    : QGLWidget(parent)
{
    qDebug()<<"widget init";
    x=0.0;xdir=false;
    frames=0;
    poly=text2polylist("Arial",40,tr("FPS"));
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
    glDepthFunc(GL_LEQUAL);         // The Type Of Depth Test To Do
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(10);
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(fpscalc()));
    timer2->start(1000);
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
    frames+=1;
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
    for (QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++){
        glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        for (QPolygonF::iterator p = (*i).begin(); p != i->end(); p++)
            glVertex3f(p->rx()*0.01f-0.3f, -p->ry()*0.01f, 0.0f);
        glEnd();
    }
    for (QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++){
        glBegin(GL_LINE_LOOP);
        for (QPolygonF::iterator p = (*i).begin(); p != i->end(); p++){
            glColor4f(1,1,1,p->ry()*0.05f+1);
            glVertex3f(p->rx()*0.01f-0.3f-(p->ry()*0.01f), p->ry()*0.01f-0.1f, 0.0f);
        }
        glEnd();
    }
    glBegin(GL_LINE);
    glColor4f(1.0f,0.0f,0.0f,0.5f);
    glVertex3f( 0.1f, 0.1f, 0.0f);
    glVertex3f(-0.1f,-0.1f, 0.0f);
    glVertex3f( 0.1f,-0.1f, 0.0f);
    glVertex3f( -0.1f, 0.1f, 0.0f);

    glColor4f(0.0f,1.0f,0.0f,0.75f);
    glVertex3f(-1.0f, -0.5f, 0.0f);
    glVertex3f(1.0f,-0.5f, 0.0f);

    glColor4f(0.0f,1.0f,0.0f,0.5f);
    glVertex3f(-1.0f, -0.75f, 0.0f);
    glVertex3f(1.0f,-0.75f, 0.0f);
    glVertex3f(0.0f, -0.5f, 0.0f);
    glVertex3f(0.0f,-1.0f, 0.0f);

    glColor4f(0.0f,1.0f,0.0f,0.25f);
    glVertex3f(-1.0f, -0.5f, 0.0f);
    glVertex3f(0.0f,-0.75f, 0.0f);
    glVertex3f(1.0f, -0.5f, 0.0f);
    glVertex3f(0.0f,-0.75f, 0.0f);

    glEnd();
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
void ClientWidget::fpscalc()
{
    qDebug()<<"fpscalc()";
    qDebug()<<"FPS: "<<frames;
    poly=text2polylist("Arial",40,QString::number(frames));
    frames=0;
}
