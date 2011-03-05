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
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);							// The Type Of Depth Test To Do
    glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
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
    glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
    glVertex3f( 0.0f, 1.0f, 0.0f);			// Move Up One Unit From Center (Top Point)
    glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
    glVertex3f(-1.0f,-1.0f, 0.0f);			// Left And Down One Unit (Bottom Left)
    glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
    glVertex3f( 1.0f,-1.0f, 0.0f);			// Right And Down One Unit (Bottom Right)
    glEnd();						// Done Drawing A Triangle
    qDebug()<<"gl paint end";
}
