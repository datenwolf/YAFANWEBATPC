#include <GL/glut.h>
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"
#include "render.h"
#include "client.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//network:
#include <enet/enet.h>





/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the window system
    glutInit(&argc, argv);    
    gl_render_engine_init();
    glutMainLoop();

    return(0);    
}
