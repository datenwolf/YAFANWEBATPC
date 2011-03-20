#include "clientwidget.h"
#include <QTimer>
#include <math.h>
#include <QDateTime>
#include <QBitmap>
#include <QApplication>
#include <QKeyEvent>
#include <GL/glut.h>

ClientWidget::ClientWidget(QGLWidget *parent)
    : QGLWidget(parent)
{
    qDebug()<<ENCAPS(tr("widget init"));
    frames=0;ftmp=0;
    clocktex=0;
    fpslabel.setStyleSheet(tr("QLabel { background: transparent; color : white; font-size: 32px; }"));
    clocklcd.setStyleSheet(tr("QLCDNumber { background: transparent; color : white; height: 32px; }"));
    hud.load("hud.png");
    emptybm.clear();
    teapot.size=F2I(0.1f);
    qsrand(0);
    for (int i=0;i<6000;i++)
    {
        float r=100;
        float theta=(float)(qrand()%628318)/100000.0f;
        float phi=(float)(qrand()%628318)/100000.0f;
        QVector3D v(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
        stars.append(v);
        qDebug()<<v;
    }
}

ClientWidget::~ClientWidget()
{
    qDebug()<<ENCAPS(tr("widget destruct"));
    if(clocktex) { deleteTexture(clocktex); clocktex=0; }
    if(fpstex) { deleteTexture(fpstex); fpstex=0; }

}

void ClientWidget::initializeGL()
{
    qDebug()<<ENCAPS(tr("gl init"));
    int argc=qApp->argc();            //quick workaround for "lvalue required for unary & operand"
    glutInit(&argc,qApp->argv());     // in "&argc()"
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);         // The Type Of Depth Test To Do
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glPointSize(1);
    glLineWidth(1.5);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(15);
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(fpscalc()));
    timer2->start(500);
#ifdef CFG_TEXTURE_FLIP
    qDebug()<<ENCAPS(tr("flipping gl textures"));
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
#endif
    fpscalc();
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    hudtex=bindTexture(hud,GL_TEXTURE_2D,GL_RGBA);
    qDebug()<<ENCAPS(tr("gl init done"));
}
void ClientWidget::drawHUD()
{
    if(hudtex){
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, hudtex );
        glBegin(GL_QUADS);
        glTexCoord2d(0.0,0.0); glVertex3d( 1.0,-1.0,1);
        glTexCoord2d(1.0,0.0); glVertex3d(-1.0,-1.0,1);
        glTexCoord2d(1.0,1.0); glVertex3d(-1.0, 1.0,1);
        glTexCoord2d(0.0,1.0); glVertex3d( 1.0, 1.0,1);
        glEnd();
        glDisable( GL_TEXTURE_2D );
    }
}

void ClientWidget::resizeGL(int w, int h)
{
    qDebug()<<ENCAPS(tr("gl resize"));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    gluPerspective(90,1/*(GLfloat)w/(GLfloat)h*/,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    qDebug()<<ENCAPS(tr("gl resize done"));
}

void ClientWidget::paintGL()
{
    frames+=1;
    qDebug()<<ENCAPS(tr("gl paint start"));
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();					// Reset The Current Modelview Matrix
    glDisable(GL_LIGHTING);
    gluLookAt(0.0, 0.0, 0.0,
              0.0, 0.0, 1.0,
              0.0, 1.0, 0.0);
//**************************************************************************************************STARS
    glColor3f(1,1,1);
    for (QList<QVector3D>::iterator i = stars.begin(); i != stars.end(); ++i)
    {
        if(i->z()>0){
            glBegin(GL_LINE);
            glColor4f(1,1,1,1);
            glVertex3f(i->x(),i->y(),i->z());
            glColor4f(1,1,1,0);
            glVertex3f(i->x(),i->y(),i->z()-(float)ftmp/5.0f);
            glEnd();
        }
    }
//**************************************************************************************************HUD
    glColor4f(1,1,1,1);
    drawHUD();
    if(fpstex){
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, fpstex );
        glBegin(GL_QUADS);
        glTexCoord2d(0.0,QT_TO_TEXTURE_ROTATION); glVertex3d(1.0,0.9,1);
        glTexCoord2d(1.0,QT_TO_TEXTURE_ROTATION); glVertex3d(0.8,0.9,1);
        glTexCoord2d(1.0,!QT_TO_TEXTURE_ROTATION); glVertex3d(0.8,1.0,1);
        glTexCoord2d(0.0,!QT_TO_TEXTURE_ROTATION); glVertex3d(1.0,1.0,1);
        glEnd();
        glDisable( GL_TEXTURE_2D );
    }
    if(clocktex){
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, clocktex );
        glBegin(GL_QUADS);
        glTexCoord2d(0.0,QT_TO_TEXTURE_ROTATION); glVertex3d(-0.8,-1.0,1);
        glTexCoord2d(1.0,QT_TO_TEXTURE_ROTATION); glVertex3d(-1.0,-1.0,1);
        glTexCoord2d(1.0,!QT_TO_TEXTURE_ROTATION); glVertex3d(-1.0,-0.9,1);
        glTexCoord2d(0.0,!QT_TO_TEXTURE_ROTATION); glVertex3d(-0.8,-0.9,1);
        glEnd();
        glDisable( GL_TEXTURE_2D );
    }
    float l[]={0.2,0.5,1,1};
    glBegin(GL_POINTS);
    glColor4f(1,0,0,1);
    glVertex3fv(l);
    glEnd();
    glLightfv(GL_LIGHT0,GL_POSITION,l);
    glEnable(GL_LIGHTING);
    glColor4f(0.8,0.8,0.8,1);
//**************************************************************************************************SCENE
    glTranslatef(-0.2,0.5,0.9);
    glRotated(180,0,1,0);
    glRotated(45,1,0,0);
    glRotated(45,0,0,1);
    teapot.render();
    qDebug()<<ENCAPS(tr("gl paint end"));
}
void ClientWidget::animate()
{
    qDebug()<<ENCAPS(tr("animate() start"));
    QDateTime now=QDateTime::currentDateTime();
    clocklcd.display(QString::number(now.time().hour()).append(":").append(QString::number(now.time().minute())));
    clocklcd.resize(clocklcd.sizeHint());
    clockpix=QPixmap(clocklcd.size());
    clockpix.fill(QColor("transparent"));
    clocklcd.render(&clockpix,QPoint(),QRegion(),RenderFlags(!DrawWindowBackground));
    if(clocktex) { deleteTexture(clocktex); clocktex=0; }
    clocktex=bindTexture(clockpix,GL_TEXTURE_2D,GL_RGBA);
    updateGL();
    qDebug()<<ENCAPS(tr("animate() end"));
}
void ClientWidget::fpscalc()
{
    qDebug()<<ENCAPS(tr("fpscalc()"));
    qDebug()<<ENCAPS(tr("FPS: "))<<(float)ftmp+frames;
    QString text=QString::number((float)ftmp+frames);
    int idx=text.indexOf('.');
    if(idx >0)
        text=text.left(idx+2);
    fpslabel.setText(text.append(tr(" FPS")));
    fpslabel.resize(fpslabel.sizeHint());
    fpspix=QPixmap(fpslabel.size());
    fpspix.fill(QColor("transparent"));
    fpslabel.render(&fpspix,QPoint(),QRegion(),RenderFlags(!DrawWindowBackground));
    if(fpstex) { deleteTexture(fpstex); fpstex=0; }
    fpstex=bindTexture(fpspix,GL_TEXTURE_2D,GL_RGBA);
    ftmp+=frames;
    ftmp/=2.0f;
    frames=0;
    qDebug()<<ENCAPS(tr("fpscalc() end"));
}
void ClientWidget::keyReleaseEvent(QKeyEvent *e){
    qDebug()<<ENCAPS(tr("keyReleaseEvent() with key: "))<<e->key();
    if(e->key()==Qt::Key_Escape && e->modifiers() == Qt::ControlModifier){
        qApp->exit();
    }else if(e->key()==Qt::Key_Escape){
        qDebug()<<ENCAPS(tr("disconnecting from server..."));
        emit disconnectFromServer();
    }
}

void ClientWidget::serverDisconnected(){
    qDebug()<<ENCAPS(tr("server disconnected."));
    qApp->exit();
}
