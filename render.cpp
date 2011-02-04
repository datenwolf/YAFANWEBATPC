#include "render.h"
#include <GL/glut.h>
#include <stdio.h>
void renderObject(obj_type_ptr p_object,float p_x,float p_y, float p_z, int p_ax, int p_ay, int p_az,GLdouble  	eyeX,
 	GLdouble  	eyeY,
 	GLdouble  	eyeZ,
 	GLdouble  	centerX,
 	GLdouble  	centerY,
 	GLdouble  	centerZ,
 	GLdouble  	upX,
 	GLdouble  	upY,
 	GLdouble  	upZ, int tex){
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity
    if(eyeX!=0||eyeY!=0||eyeZ!=0||centerX!=0||centerY!=0||centerZ!=0||upX!=0||upY!=0||upZ!=0)
	  gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
    p_object->matrix[0][0]=(matr_cos_table[0]);
    p_object->matrix[0][1]=(matr_sin_table[0]);
    p_object->matrix[0][2]=(-matr_sin_table[0]);
    p_object->matrix[1][0]=(-matr_sin_table[0]);
    p_object->matrix[1][1]=(matr_cos_table[0]);
    p_object->matrix[1][2]=(matr_sin_table[0]);
    p_object->matrix[2][0]=(matr_sin_table[0]);
    p_object->matrix[2][1]=(-matr_sin_table[0]);
    p_object->matrix[2][2]=(matr_cos_table[0]);
    p_object->matrix[3][0]=p_x;
    p_object->matrix[3][1]=p_y;
    p_object->matrix[3][2]=p_z;    
    ObjRotate(p_object, p_ax, p_ay, p_az);
    glPushMatrix();
    glMultMatrixf(&p_object->matrix[0][0]);
    if (tex!=-1){
      glBindTexture(GL_TEXTURE_2D, tex);
      glEnable(GL_TEXTURE_2D);
    }else{
      if (p_object->id_texture!=-1){
        glBindTexture(GL_TEXTURE_2D, p_object->id_texture);
        glEnable(GL_TEXTURE_2D);
      }else{
        glDisable(GL_TEXTURE_2D);
      }
    }

      glBegin(GL_TRIANGLES);
      int j;
      for (j=0;j<p_object->polygons_qty;j++)
      {
        glNormal3f( p_object->normal[ p_object->polygon[j].a ].x,
              p_object->normal[ p_object->polygon[j].a ].y,
              p_object->normal[ p_object->polygon[j].a ].z);
        glTexCoord2f( p_object->mapcoord[ p_object->polygon[j].a ].u,
                p_object->mapcoord[ p_object->polygon[j].a ].v);
        glVertex3f( p_object->vertex[ p_object->polygon[j].a ].x,
              p_object->vertex[ p_object->polygon[j].a ].y,
              p_object->vertex[ p_object->polygon[j].a ].z);

        glNormal3f( p_object->normal[ p_object->polygon[j].b ].x,
              p_object->normal[ p_object->polygon[j].b ].y,
              p_object->normal[ p_object->polygon[j].b ].z);
        glTexCoord2f( p_object->mapcoord[ p_object->polygon[j].b ].u,
                p_object->mapcoord[ p_object->polygon[j].b ].v);
        glVertex3f( p_object->vertex[ p_object->polygon[j].b ].x,
              p_object->vertex[ p_object->polygon[j].b ].y,
              p_object->vertex[ p_object->polygon[j].b ].z);
          
        glNormal3f( p_object->normal[ p_object->polygon[j].c ].x,
              p_object->normal[ p_object->polygon[j].c ].y,
              p_object->normal[ p_object->polygon[j].c ].z);
        glTexCoord2f( p_object->mapcoord[ p_object->polygon[j].c ].u,
                p_object->mapcoord[ p_object->polygon[j].c ].v);
        glVertex3f( p_object->vertex[ p_object->polygon[j].c ].x,
              p_object->vertex[ p_object->polygon[j].c ].y,
              p_object->vertex[ p_object->polygon[j].c ].z);

      }
      glEnd();
    glPopMatrix();
}
