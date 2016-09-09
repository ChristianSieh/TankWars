#include <iostream>
#include <GL/freeglut.h>
#include "Terrain.h"
#include "Tank.h"

using namespace std;

const float Red[] = { 1.0, 0.0, 0.0 };
const float Blue[] = { 0.0, 0.0, 1.0 };
Terrain myTerrain;
Tank player1(myTerrain.points[10].x - 6, myTerrain.points[10].y - 8, Red, 110);
Tank player2(myTerrain.points[myTerrain.points.size() - 10].x - 6, myTerrain.points[myTerrain.points.size() - 10].y - 8, Blue, 70);

void init( void );
void display( void );
void special( int key, int x, int y);

int main( int argc, char *argv[] )
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tank Wars");

    init();
    glutDisplayFunc( display );
    glutSpecialFunc( special );
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

    myTerrain.DrawTerrain();

    player1.DrawTank();
    player2.DrawTank();

    glFlush();
}

void special( int key, int x, int y )
{
    // process keypresses
    switch ( key )
    {
        case GLUT_KEY_LEFT:
            player1.MoveLeft(myTerrain.points);
            break;
        case GLUT_KEY_RIGHT:
            player1.MoveRight(myTerrain.points);
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
    }
    glutPostRedisplay();
}
