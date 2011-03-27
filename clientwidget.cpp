#include "clientwidget.h"
#include <QTimer>
#include <math.h>
#include <QDateTime>
#include <QBitmap>
#include <QApplication>
#include <QKeyEvent>
#include <GL/glut.h>
#include <FTGL/ftgl.h>
ClientWidget::ClientWidget(QGLWidget *parent)
    : QGLWidget(parent)
{
    qDebug()<<ENCAPS(tr("widget init"));
    frames=0;ftmp=0;
    hud.load("hud.png");
    emptybm.clear();
    teapot.size=F2I(0.1f);
    qsrand(0);
    for (int i=0;i<6000;i++)
    {
        float r=999;
        float theta=(float)(qrand()%628318)/100000.0f;
        float phi=(float)(qrand()%628318)/100000.0f;
        QVector3D v(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
        stars.append(v);
        qDebug()<<v;
    }
}

void ClientWidget::renderFont(FTPixmapFont* f,QString s, float x,float y,int lr,int tb){
    FTPoint size=font->BBox(s.toUtf8().data()).Upper();
    float px=0;
    float py=0;
    if(lr==CWRF_LEFT){
        px=x;
    }else if(lr==CWRF_RIGHT){
        px=width()-size.Xf()-x;
    }else if(lr==CWRF_CENTER){
        px=((width()-size.Xf())/2)+x;
    }
    if(tb==CWRF_BOTTOM){
        py=y;
    }else if(tb==CWRF_TOP){
        py=height()-size.Yf()-y;
    }else if(tb==CWRF_CENTER){
        py=((height()-size.Yf())/2)+y;
    }
    f->Render(s.toUtf8().data(),-1,FTPoint(px,py));
}

ClientWidget::~ClientWidget()
{
    qDebug()<<ENCAPS(tr("widget destruct"));
}

void ClientWidget::initializeGL()
{
    qDebug()<<ENCAPS(tr("gl init"));
    int argc=qApp->argc();            //quick workaround for "lvalue required for unary & operand"
    glutInit(&argc,qApp->argv());     // in "&argc()"
    font=new FTPixmapFont("arial.ttf");
    font->FaceSize(72);
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
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    hudtex=bindTexture(hud,GL_TEXTURE_2D,GL_RGBA);
    bunny.load("bunny.ctm");    bunny.CalcNormals(0.05);

    lightingprogram.addShaderFromSourceCode(QGLShader::Vertex,
                                            "varying vec3 N;\n"
                                            "varying vec3 v;\n"
                                            "void main(void) {\n"
                                            "   v = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
                                            "   N = normalize(gl_NormalMatrix * gl_Normal);\n"
                                            "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
                                            "}\n");
    lightingprogram.addShaderFromSourceFile(QGLShader::Fragment,"light.frag");
    lightingprogram.link();
    lightingprogram.setUniformValue("MAX_LIGHTS",2);

    qDebug()<<ENCAPS(tr("gl init done"));
}

void ClientWidget::resizeGL(int w, int h)
{
    qDebug()<<ENCAPS(tr("gl resize"));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    qDebug()<<ENCAPS(tr("gl resize done"));
}

void ClientWidget::paintGL()
{
    frames+=1;
    qDebug()<<ENCAPS(tr("gl paint start"));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,(float)width()/(float)height(),0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//**************************************************************************************************SCENE
    float l[]={-2,0,1,1};
    glLightfv(GL_LIGHT0,GL_POSITION,l);
    l[0]=-l[0];
    glLightfv(GL_LIGHT1,GL_POSITION,l);
    lightingprogram.bind();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glColor4f(0.8,0.8,0.8,1);
    glLoadIdentity();
    gluLookAt(me.position.x(), me.position.y(),      me.position.z(),
              me.position.x(), me.position.y(),      me.position.z()+1.0f,
              me.position.x(), me.position.y()+1.0f, me.position.z());
    glTranslatef(-0.1,0.2,0.5);
    glRotated(180,0,1,0);
    glRotated(30,1,0,0);
    glRotated(5,0,0,1);
    GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,128);
    teapot.render();
    glLoadIdentity();
    gluLookAt(me.position.x(), me.position.y(),      me.position.z(),
              me.position.x(), me.position.y(),      me.position.z()+1.0f,
              me.position.x(), me.position.y()+1.0f, me.position.z());
    glTranslatef(0.1,-0.2,1);
    glColor4f(0.8,0.8,0.8,1);
    glScaled(0.05,0.05,0.05);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,128);
    bunny.render();
    lightingprogram.release();
//**************************************************************************************************HUD
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,width(),0, height(), -1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();					// Reset The Current Modelview Matrix
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor4f(1,1,1,1);
    if(hudtex){
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, hudtex );
        glBegin(GL_QUADS);
        glTexCoord2d(0.0,0.0); glVertex3d(-1.0,-1.0,-1);
        glTexCoord2d(1.0,0.0); glVertex3d( 1.0,-1.0,-1);
        glTexCoord2d(1.0,1.0); glVertex3d( 1.0, 1.0,-1);
        glTexCoord2d(0.0,1.0); glVertex3d(-1.0, 1.0,-1);
        glEnd();
        glDisable( GL_TEXTURE_2D );
    }
    renderFont(font,fps,10,10,CWRF_LEFT,CWRF_TOP);
    renderFont(font,clock,10,10,CWRF_RIGHT,CWRF_BOTTOM);
    qDebug()<<ENCAPS(tr("gl paint end"));
}
void ClientWidget::animate()
{
    qDebug()<<ENCAPS(tr("animate() start"));
    QDateTime now=QDateTime::currentDateTime();
    QString h=QString::number(now.time().hour());
    QString m=QString::number(now.time().minute());
    if(now.time().hour()<10) h.prepend("0");
    if(now.time().minute()<10) m.prepend("0");
    clock=h.append(":").append(m);
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
    fps=text.append(tr(" FPS"));
    ftmp+=frames;
    ftmp/=2.0f;
    frames=0;
    qDebug()<<ENCAPS(tr("fpscalc() end"));
}
void ClientWidget::keyReleaseEvent(QKeyEvent *e){
    qDebug()<<ENCAPS(tr("keyReleaseEvent() with key: "))<<e->key();
    switch(e->key()){
    case Qt::Key_Plus:
        me.position.setZ(me.position.z()+1);
        break;
    case Qt::Key_Minus:
        me.position.setZ(me.position.z()-1);
        break;
    case Qt::Key_Escape:
        if(e->modifiers() == Qt::ControlModifier){
            qApp->exit();
        }else{
            qDebug()<<ENCAPS(tr("disconnecting from server..."));
            emit disconnectFromServer();
        }
        break;
    }
}

void ClientWidget::serverDisconnected(){
    qDebug()<<ENCAPS(tr("server disconnected."));
    qApp->exit();
}
