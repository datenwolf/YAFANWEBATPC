#include "ctmspaceobject.h"
#include <QDebug>
#include <math.h>
CTMSpaceObject::CTMSpaceObject()
{
}

void CTMSpaceObject::render(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT,0,normals);
    glDrawElements(GL_TRIANGLES,  triCount*3, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
void CTMSpaceObject::load(QString fn){
    filename=fn;
    ctm.Load(filename.toUtf8().data());
    vertCount = ctm.GetInteger(CTM_VERTEX_COUNT);
    triCount = ctm.GetInteger(CTM_TRIANGLE_COUNT);
    indices =(CTMuint*) ctm.GetIntegerArray(CTM_INDICES);
    vertices =(CTMfloat*) ctm.GetFloatArray(CTM_VERTICES);
    bool nc=false;
    if((bool) ctm.GetInteger(CTM_HAS_NORMALS)){
        normals =(CTMfloat*) ctm.GetFloatArray(CTM_NORMALS);
    }else{
        normals = (CTMfloat*) malloc(triCount*sizeof(CTMfloat)+5);
        CalcNormals();
        nc=true;
    }
    qDebug()<<"CTM:"<<fn<<"vertCount:"<<vertCount<<"triCount:"<<triCount<<"normalCalc:"<<nc;
}
void CTMSpaceObject::CalcNormals()
 {
    for(int i=0;i<triCount;i+=3){
        float p1_x=vertices[indices[i       ]       ];
        float p1_y=vertices[indices[i       ]     +1];
        float p1_z=vertices[indices[i       ]     +2];

        float p2_x=vertices[indices[i     +1]       ];
        float p2_y=vertices[indices[i     +1]     +1];
        float p2_z=vertices[indices[i     +1]     +2];

        float p3_x=vertices[indices[i     +2]       ];
        float p3_y=vertices[indices[i     +2]     +1];
        float p3_z=vertices[indices[i     +2]     +2];

        float var1_x = p2_x - p1_x;
        float var1_y = p2_y - p1_y;
        float var1_z = p2_z - p1_z;

        float var2_x = p3_x - p1_x;
        float var2_y = p3_y - p1_y;
        float var2_z = p3_z - p1_z;

        float normal_x = (var1_y * var2_z) - (var2_y * var1_z);
        float normal_y = (var1_z * var2_x) - (var2_z * var1_x);
        float normal_z = (var1_x * var2_y) - (var2_x * var1_y);

        float vLen = sqrt( (normal_x * normal_x) + (normal_y * normal_y) + (normal_z * normal_z) );

        normal_x /= vLen;
        normal_y /= vLen;
        normal_z /= vLen;
        normals[i]=normal_x;
        normals[i+1]=normal_y;
        normals[i+2]=normal_z;
    }
}
QDataStream &operator<<(QDataStream& s, const CTMSpaceObject& o){
    s << "%CTMSPACEOBJECT%";
    s << o.objtype;
    s << o.flags;
    s << o.position;
    s << o.velocity;
    s << o.rotation; //right hand rule rotation around axes.
    s << o.rotvel;
    s << o.size;
    s << o.filename;
    return s;
}

QDataStream &operator>>(QDataStream& s, CTMSpaceObject& o){
    char* n;
    s >> n;
    if(QString("%CTMSPACEOBJECT%").compare(n)==0){
        s >> o.objtype;
        s >> o.flags;
        s >> o.position;
        s >> o.velocity;
        s >> o.rotation;
        s >> o.rotvel;
        s >> o.size;
        s >> o.filename;
        o.load(o.filename);
    }
    return s;
}
