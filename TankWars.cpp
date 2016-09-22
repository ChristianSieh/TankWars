#include <iostream>
#include <GL/freeglut.h>
#include "Terrain.h"
#include "Tank.h"
#include "Projectile.h"
#include "Explosion.h"

using namespace std;

const int EscapeKey = 27;
const float Red[] = { 1.0, 0.0, 0.0 };
const float Blue[] = { 0.0, 0.0, 1.0 };
const float Orange[] = { 1.0, 0.647, 0.0 };
Terrain myTerrain;
Tank player1(myTerrain.points[10].x - 6, myTerrain.points[10].y - 8, Red, 300);
Tank player2(myTerrain.points[myTerrain.points.size() - 10].x - 6, myTerrain.points[myTerrain.points.size() - 10].y - 8, Blue, 240);
vector<Projectile> player1Projectiles;
vector<Projectile> player2Projectiles;
int ScreenWidth = 800;
int ScreenHeight = 600;
int PlayerTurn = 1;

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
    glutIdleFunc( display ); 
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

    //Redraw all projectiles for player1, this is here in case I add something that allows more then 1
    for(int i = 0; i < player1Projectiles.size(); i++)
    {
        //If the projectile goes out of bounds delete it
        if(player1Projectiles[i]._xPosition > ScreenWidth || player1Projectiles[i]._xPosition < 0 || 
            player1Projectiles[i]._yPosition > ScreenHeight)
        {
            player1Projectiles.erase(player1Projectiles.begin() + i);
        }
        else
        {
            player1Projectiles[i].DrawProjectile();
            if(player1Projectiles[i].TankCollision(player2) || player1Projectiles[i].TerrainCollision(myTerrain.points))
            {
                Explosion exp(player1Projectiles[i]._xPosition, player1Projectiles[i]._yPosition, Orange);
                player1Projectiles.erase(player1Projectiles.begin() + i);
                
            }
        }
    }

    //Redraw all projectiles for player 2, this is here in case I add something that allows more then 1
    for(int i = 0; i < player2Projectiles.size(); i++)
    {
        //If the projectile goes out of bounds delete it
        if(player2Projectiles[i]._xPosition > ScreenWidth || player2Projectiles[i]._xPosition < 0 || 
            player2Projectiles[i]._yPosition > ScreenHeight)
        {
            player2Projectiles.erase(player2Projectiles.begin() + i);
        }
        else
        {
            player2Projectiles[i].DrawProjectile();
            if(player2Projectiles[i].TankCollision(player1) || player2Projectiles[i].TerrainCollision(myTerrain.points))
            {
                Explosion exp(player2Projectiles[i]._xPosition, player2Projectiles[i]._yPosition, Orange);
                player2Projectiles.erase(player2Projectiles.begin() + i);
            }
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
            if(PlayerTurn == 1)
                player1.MoveLeft(myTerrain.points);
            else
                player2.MoveLeft(myTerrain.points);
            break;
        case GLUT_KEY_RIGHT:
            if(PlayerTurn == 1)
                player1.MoveRight(myTerrain.points);
            else
                player2.MoveRight(myTerrain.points);
            break;
        case GLUT_KEY_UP:
            if(PlayerTurn == 1)
                player1.ChangeAngle(1);
            else
                player2.ChangeAngle(1);
            break;
        case GLUT_KEY_DOWN:
            if(PlayerTurn == 1)
                player1.ChangeAngle(-1);
            else
                player2.ChangeAngle(-1);
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
            //cout << player1._xPosition << " " << player1._yPosition << " " << player1._velocity << " " << player1._angle << endl;
            if(PlayerTurn == 1)
            {            
                Projectile proj(player1._xPosition, player1._yPosition, player1._velocity, player1._angle);
                player1Projectiles.push_back(proj);
                PlayerTurn = 2;
            }
            else
            {
                Projectile proj(player2._xPosition, player2._yPosition, player2._velocity, player2._angle);
                player2Projectiles.push_back(proj);
                PlayerTurn = 1;
            }
            glutPostRedisplay();
            break;
        }
        case 43:
            if(PlayerTurn == 1)
                player1.ChangeVelocity(1);
            else
                player2.ChangeVelocity(1);
            break;

        case 45:
            if(PlayerTurn == 1)
                player1.ChangeVelocity(-1);
            else
                player2.ChangeVelocity(-1);
            break;

        // anything else redraws window
        default:
            glutPostRedisplay();
            break;
    }
}
