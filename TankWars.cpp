#include <iostream>
#include <GL/freeglut.h>
#include "Terrain.h"

using namespace std;

void init( void );
void display( void );

int main( int argc, char *argv[] )
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tank Wars");

    Terrain myTerrain;

    myTerrain.DisplaceTerrain(4, 50);

    init();
    glutDisplayFunc( myTerrain.DrawTerrain );
    glutMainLoop();

    return 0;
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 600.0, 0.0);
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    glColor3f(0.0, 0.4, 0.2);

    glBegin( GL_LINE_STRIP );
        glVertex2f( 0, 400 );
        glVertex2f( 250,  400 );
        glVertex2f( 400, 150 );
        glVertex2f(  550,  400 );
        glVertex2f(  800, 400 );
    glEnd();

    glFlush();
}
