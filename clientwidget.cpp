#include "clientwidget.h"
#include <QTimer>
#include <math.h>
#include <QDateTime>
#include <QBitmap>
#include <QApplication>
#include <QKeyEvent>

QList<QPolygonF> text2polylist(char* font, int size, QString str){
    QPainterPath path;
    path.addText(QPointF(0, 0), QFont(font, size), QString(str));
    return path.toSubpathPolygons();
}



ClientWidget::ClientWidget(QGLWidget *parent)
    : QGLWidget(parent)
{
    qDebug()<<"widget init";
    frames=0;
    fpslabel.setStyleSheet("QLabel { background: transparent; color : white; font-size: 32px; }");
    led1ON=false;
    for(float t = 0; t <= 6.28f; t += 0.06f){
        radar.append(QPointF(0.4f * cos(t), 0.2f * sin(t) -0.8f));
    }
    for(float t = 0; t <= 6.28f; t += 0.12f){
        halfradar.append(QPointF(0.2f * cos(t), 0.1f * sin(t) -0.8f));
        led1circle.append(QPointF(cos(t)*0.02f-0.9f, sin(t)*0.02f-0.8f));
    }
    radar_tl=QPointF(0.4f * cos(0.785398163), 0.2f * sin(0.785398163) -0.8f);
    radar_tr=QPointF(0.4f * cos(2.35619449), 0.2f * sin(2.35619449) -0.8f);
}

ClientWidget::~ClientWidget()
{
    qDebug()<<"widget destruct";
}

void ClientWidget::initializeGL()
{
    qDebug()<<"gl init";
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
    timer->start(20);
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(fpscalc()));
    timer2->start(500);
#ifdef CFG_TEXTURE_FLIP
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
#endif
    fpscalc();
    qDebug()<<"gl init done";
}
void ClientWidget::drawHUD()
{
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor4f(1,0,0,0.75f);
    glVertex2d(0,0);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINE); //crosshair
    glColor4f(1,0,0,0.5f);
    glVertex2d(  0.1f,    0.1f);
    glVertex2d( -0.1f,   -0.1f);

    glVertex2d(  0.1f,   -0.1f);
    glVertex2d( -0.1f,    0.1f);
    glEnd();
    glLineWidth(4);
    glBegin(GL_LINE);
    glColor4f(1,0,0,1);
    glVertex2d( -0.1f,    0.0f);
    glVertex2d( -0.2f,    0.0f);

    glVertex2d(  0.1f,    0.0f);
    glVertex2d(  0.2f,    0.0f);

    glVertex2d(  0.0f,   -0.1f);
    glVertex2d(  0.0f,   -0.2f);

    glVertex2d(  0.0f,    0.1f);
    glVertex2d(  0.0f,    0.2f);
    glEnd();
    glLineWidth(1.5);
    glBegin(GL_LINE);
    glColor4f(0,1,0,1);//instruments
    glVertex2d(  -1,     -0.6f);
    glVertex2d(   1,     -0.6f);
    glEnd();
    glBegin(GL_QUADS);
    glColor4f(0,1,0,0.5);
    glVertex2f(-1,-0.6f);
    glVertex2f( 1,-0.6f);
    glVertex2f( 1,-1);
    glVertex2f(-1,-1);
    glEnd();
    glBegin(GL_POLYGON);
    glColor4f(0,1,0,0.25);
    for (QList<QPointF>::iterator i = radar.begin(); i != radar.end(); i++)
        glVertex2f(i->x(),i->y());
    glEnd();
    glBegin(GL_POLYGON);
    for (QList<QPointF>::iterator i = halfradar.begin(); i != halfradar.end(); i++)
        glVertex2f(i->x(),i->y());
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor4f(0,1,0,1);
    for (QList<QPointF>::iterator i = radar.begin(); i != radar.end(); i++)
        glVertex2f(i->x(),i->y());
    glEnd();
    glBegin(GL_POLYGON);//LED1
    if(led1ON){
        glColor4f(1,0,0,1);
    }else{
        glColor4f(0.3,0.1,0.1,1);
    }
    for (QList<QPointF>::iterator i = led1circle.begin(); i != led1circle.end(); i++)
        glVertex2f(i->x(),i->y());
    glEnd();
    glColor4f(0,1,0,1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(radar_tl.x(),radar_tl.y());
    glVertex2f(0,-0.8f);
    glVertex2f(radar_tr.x(),radar_tr.y());
    glEnd();
    glBegin(GL_LINE);
    glVertex2f(0,-0.8f);
    glVertex2f(0,-1);
    glVertex2f(0,-0.7f);
    glVertex2f(0,-0.6);
    glEnd();
    glPointSize(1);
    glLineWidth(1.5);
}

void ClientWidget::resizeGL(int w, int h)
{
    qDebug()<<"gl resize";
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, (GLint)w, (GLint)h);
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,
              0.0, 0.0, -1.0,
              0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    qDebug()<<"gl resize done";
}

void ClientWidget::paintGL()
{
    frames+=1;
    qDebug()<<"gl paint start";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glLoadIdentity();					// Reset The Current Modelview Matrix
    qsrand(0);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    for (int i=0;i<100;i++)
    {
        glVertex2f(((float)(qrand()%100-50))/50.0f,((float)(qrand()%100-50))/50.0f);
    }
    glEnd();
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, fpstex );
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,0.9);
    glTexCoord2d(1.0,0.0); glVertex2d(-0.8,0.9);
    glTexCoord2d(1.0,1.0); glVertex2d(-0.8,1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,1.0);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    drawHUD();
    qDebug()<<"gl paint end";
}
void ClientWidget::animate()
{
    qDebug()<<"animate() start";
    led1ON=QDateTime::currentDateTime().toTime_t()%2;
    updateGL();
    qDebug()<<"animate() end";
}
void ClientWidget::fpscalc()
{
    qDebug()<<"fpscalc()";
    qDebug()<<"FPS: "<<frames*2;
    fpslabel.setText(QString::number(frames*2).append(" FPS"));
    qDebug()<<"label text updated";
    fpslabel.resize(fpslabel.sizeHint());
    qDebug()<<"label resized";
    fpspix=QPixmap(fpslabel.size());
    qDebug()<<"pix resized";
    fpspix.fill(QColor("transparent"));
    qDebug()<<"pix filled";
    fpslabel.render(&fpspix,QPoint(),QRegion(),RenderFlags(!DrawWindowBackground));
    qDebug()<<"label rendered to pix";
    deleteTexture(fpstex);
    qDebug()<<"tex deleted";
    fpstex=bindTexture(fpspix,GL_TEXTURE_2D,GL_RGBA);
    qDebug()<<"tex bound";
    frames=0;
    qDebug()<<"fpscalc() end";
}
void ClientWidget::keyReleaseEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Escape && e->modifiers() == Qt::ControlModifier){
        qApp->exit();
    }
}
