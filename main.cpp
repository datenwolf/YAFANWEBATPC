
#include <GL/glut.h>
#include <stdlib.h>
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"
#include "render.h"
#include <time.h>
#include <math.h>
#include <stdio.h>


/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// The width and height of your window, change them as you like
int screen_width=640;
int screen_height=480;

// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

//Lights settings
GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 100.0f, 0.0f, -10.0f, 1.0f };

//Materials settings
GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_diffuse[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_shininess[]= { 1.0f };

float rt;
float rt2;
float rt3;
float rtdiff;
float rotfac_raw=100.0;
float rotfac=rotfac_raw/(float)CLOCKS_PER_SEC;
int rot=0;
bool rototherdir=true;


float fps_count=0;
int fps_tmp=0;

int cx=0;
int cy=0;
int cz=0;


int suntex;
/**********************************************************
 *
 * SUBROUTINE init(void)
 *
 * Used to initialize OpenGL and to setup our world
 *
 *********************************************************/

void init(void)
{
	MatrGenerateLookupTab();

    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear background color to black

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);  

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f); // We define the "viewing volume"
   
	//Lights initialization and activation
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    //Materials initialization and activation
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_specular);
    glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);    

	//Other initializations
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction (OpenGL... thank you so much!)
    glEnable(GL_TEXTURE_2D); // Texture mapping ON
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
	glEnable(GL_CULL_FACE); // Enable the back face culling
    glEnable(GL_DEPTH_TEST); // Enable the depth test (also called z buffer)

	//Objects loading
	ObjLoad ("models/fighter1.3ds","models/skull.bmp",             -10.0, 0.0, -30.0,    900,0,0);
	ObjLoad ("models/fighter2.3ds",'\0',                     10.0, 0.0, -30.0,    900,0,0);
	ObjLoad ("models/fighter3.3ds","models/spaceshiptexture.bmp",    0.0, 0.0, -30.0,    900,0,0);
	ObjLoad ("models/planet.3ds","models/planet_uv_perlin.bmp",                     10.0, 0.0, -30.0,    900,0,0);
  suntex=LoadBMP("models/sun_uv.bmp");
}



/**********************************************************
 *
 * SUBROUTINE resize(int p_width, int p_height)
 *
 * This routine must be called everytime we resize our window.
 *
 * Input parameters: p_width = width in pixels of our viewport
 *					 p_height = height in pixels of our viewport
 * 
 *********************************************************/

void resize (int p_width, int p_height)
{
	if (screen_width==0 && screen_height==0) exit(0);
    screen_width=p_width; // We obtain the new screen width values and store it
    screen_height=p_height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}



/**********************************************************
 *
 * SUBROUTINE keyboard(unsigned char p_key, int p_x, int p_y)
 *
 * Used to handle the keyboard input (ASCII Characters)
 *
 * Input parameters: p_key = ascii code of the key pressed
 *					 p_x = not used, keeped to maintain compatibility with glut function
 *                   p_y = not used, keeped to maintain compatibility with glut function
 * 
 *********************************************************/

void keyboard(unsigned char p_key, int p_x, int p_y)
{  
    switch (p_key)
    {
		case 'r': case 'R':
            if (filling==0)
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
                filling=1;
            }   
            else 
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
                filling=0;
            }
        break;
		case 'f': case 'F':
        printf("FPS: %f\n",fps_count);
        break;
		case 'w': case 'W':
        cy+=5;
        break;
		case 's': case 'S':
        cy-=5;
        break;
		case 'd': case 'D':
        cx+=5;
        break;
		case 'a': case 'A':
        cx-=5;
        break;
		case 'q': case 'Q':
        cz+=5;
        break;
		case 'e': case 'E':
        cz-=5;
        break;
		case 27:
			exit(0);
		break;
    }
}



/**********************************************************
 *
 * SUBROUTINE keyboard(int p_key, int p_x, int py)
 *
 * Used to handle the keyboard input (not ASCII Characters)
 *
 * Input parameters: p_key = code of the key pressed
 *					 p_x = not used, keeped to maintain compatibility with glut function
 *                   p_y = not used, keeped to maintain compatibility with glut function
 * 
 *********************************************************/

void keyboard_s (int p_key, int p_x, int py)
{
    switch (p_key)
    {
        case GLUT_KEY_UP:
        rotfac_raw+=100.0;
        rotfac=rotfac_raw/(float)CLOCKS_PER_SEC;
        break;
        case GLUT_KEY_DOWN:
        rotfac_raw-=100.0;
        rotfac=rotfac_raw/(float)CLOCKS_PER_SEC;
        break;
        case GLUT_KEY_LEFT:
        break;
        case GLUT_KEY_RIGHT:
        break;
        case GLUT_KEY_PAGE_UP:
    		break;
        case GLUT_KEY_PAGE_DOWN:
    		break;
    }
}



/**********************************************************
 *
 * SUBROUTINE display(void)
 *
 * This is our main rendering subroutine, called each frame
 * 
 *********************************************************/
void display(void)
{
    fps_tmp++;
    rt2=clock();
    rtdiff=(rt2-rt)*rotfac;
    if(fps_tmp>=100){
      fps_count=100.0*(rt2-rt3)/(float)CLOCKS_PER_SEC;
      fps_tmp=0;
      rt3=rt2;
    }
    rt=rt2;
    if(rototherdir){
      rot+=rtdiff;
    }else{
      rot-=rtdiff;
    }
    if((rototherdir && rot>=3600) || (!rototherdir && rot <= 0)){ rototherdir=!rototherdir; }

    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    for (i=0;i<obj_qty;i++)
    {
        renderObject(&object[i],10.0*(i-1), 0.0,-30.0,   900,0,rot,   cx,cy,cz,   cx,cy,cz-1,   0,1,0);
    }
    renderObject(&object[i-1],10.0*(i-1), 0.0,-30.0,   900,0,rot,   cx,cy,cz,   cx,cy,cz-1,   0,1,0, suntex);
    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}



/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the window system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Yafanwebatpc");    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
