#include <iostream>
#include <GL/freeglut.h>
#include "Terrain.h"
#include "Tank.h"
#include "Projectile.h"

using namespace std;

const int EscapeKey = 27;
const float Red[] = { 1.0, 0.0, 0.0 };
const float Blue[] = { 0.0, 0.0, 1.0 };
Terrain myTerrain;
Tank player1(myTerrain.points[10].x - 6, myTerrain.points[10].y - 8, Red, 300);
Tank player2(myTerrain.points[myTerrain.points.size() - 10].x - 6, myTerrain.points[myTerrain.points.size() - 10].y - 8, Blue, 70);
vector<Projectile> player1Projectiles;
vector<Projectile> player2Projectiles;
int ScreenWidth = 800;
int ScreenHeight = 600;

void init( void );
void display( void );
void special( int key, int x, int y);
void keyboard( unsigned char key, int x, int y );

int main( int argc, char *argv[] )
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutCreateWindow("Tank Wars");

    init();
    glutDisplayFunc( display );
    glutSpecialFunc( special );
    glutKeyboardFunc( keyboard ); 
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

    for(int i = 0; i < player1Projectiles.size(); i++)
    {
        if(player1Projectiles[i]._xPosition > ScreenWidth || player1Projectiles[i]._xPosition < 0 || 
            player1Projectiles[i]._yPosition > ScreenHeight || player1Projectiles[i]._yPosition < 0)
        {
            player1Projectiles.erase(player1Projectiles.begin() + i);
        }
        else
        {
            player1Projectiles[i].DrawProjectile();
        }
    }

    for(int i = 0; i < player2Projectiles.size(); i++)
    {
        if(player2Projectiles[i]._xPosition > ScreenWidth || player2Projectiles[i]._xPosition < 0 || 
            player2Projectiles[i]._yPosition > ScreenHeight || player2Projectiles[i]._yPosition < 0)
        {
            player1Projectiles.erase(player1Projectiles.begin() + i);
        }
        else
        {
            player2Projectiles[i].DrawProjectile();
        }
    }

    glutSwapBuffers();
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
            player1.ChangeAngle(1);
            break;
        case GLUT_KEY_DOWN:
            player1.ChangeAngle(-1);
            break;
    }
    glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y )
{
    // process keypresses
    switch ( key )
    {
        // Escape quits program
        case EscapeKey:
            exit( 0 );
            break;
        
        case 32:
        {
            cout << player1._xPosition << " " << player1._yPosition << " " << player1._velocity << " " << player1._angle << endl;
            Projectile proj(player1._xPosition, player1._yPosition, player1._velocity, player1._angle);
            player1Projectiles.push_back(proj);
            glutPostRedisplay();
            break;
        }
        case 43:
            player1.ChangeVelocity(1);
            break;

        case 45:
            player1.ChangeVelocity(-1);
            break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}
