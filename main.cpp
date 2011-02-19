#include <GL/glut.h>
#ifdef RUN_SERVER
#include "server.h"
#else
#include "client.h"
#include "render.h"
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"
#endif
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//network:
#include <enet/enet.h>
#ifdef RUN_TESTS
#include "tests.h"
#endif





/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    srand(time(NULL));
#ifdef RUN_TESTS
    printf("This is YAFANWEBATPC version %s, running the test suite.\n",VERSION);
    return tests_run_suite(&argc,argv);
#else
#ifdef RUN_SERVER
    return server_loop(&argc,argv);
#else
    printf("This is YAFANWEBATPC version %s, running the game.\n",VERSION);
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the window system
    glutInit(&argc, argv);
    gl_render_engine_init(&argc,argv);
#endif
#endif
    return(0);
}
