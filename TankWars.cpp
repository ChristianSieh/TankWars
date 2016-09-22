#include <iostream>
#include <GL/freeglut.h>
#include <random>
#include "Terrain.h"
#include "Tank.h"
#include "Projectile.h"
#include "Explosion.h"

using namespace std;

const int EscapeKey = 27;
const float Red[] = { 1.0, 0.0, 0.0 };
const float Blue[] = { 0.0, 0.0, 1.0 };
const float Orange[] = { 1.0, 0.647, 0.0 };
const float Black[] = { 0.0, 0.0, 0.0 };
float ScreenWidth = 800;
float ScreenHeight = 600;
int PlayerTurn = 1;

//Using C++11 to get a random number since it's supposed to be better
random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> dist(3.0, 15.0);
int player1Point = (int)dist(mt);
int player2Point = (int)dist(mt);

Terrain myTerrain;
Tank player1(myTerrain.points[player1Point].x, myTerrain.points[player1Point].y, Red, 300);
Tank player2(myTerrain.points[myTerrain.points.size() - player2Point].x, myTerrain.points[myTerrain.points.size() - player2Point].y, Blue, 240);
vector<Projectile> player1Projectiles;
vector<Projectile> player2Projectiles;
vector<Explosion> explosions;
void reset();

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
    gluOrtho2D(0.0, ScreenWidth, ScreenHeight, 0.0);
}

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    myTerrain.DrawTerrain();

    player1.DrawTank();
    player2.DrawTank();

    for(unsigned int i = 0; i < explosions.size(); i++)
    {
        explosions[i].DrawExplosion();
    }

    //Redraw all projectiles for player1, this is here in case I add something that allows more then 1
    for(unsigned int i = 0; i < player1Projectiles.size(); i++)
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
            if(player1Projectiles[i].TankCollision(player2))
            {
                Explosion exp(player1Projectiles[i]._xPosition, player1Projectiles[i]._yPosition, Orange);
                explosions.push_back(exp);
                player1Projectiles.erase(player1Projectiles.begin() + i);
                reset();
            }
            if(player1Projectiles[i].TerrainCollision(myTerrain.points))
            {
                Explosion exp(player1Projectiles[i]._xPosition, player1Projectiles[i]._yPosition, Orange);
                player1Projectiles.erase(player1Projectiles.begin() + i);
            }
        }
    }

    //Redraw all projectiles for player 2, this is here in case I add something that allows more then 1
    for(unsigned int i = 0; i < player2Projectiles.size(); i++)
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
            if(player2Projectiles[i].TankCollision(player1))
            {
                Explosion exp(player2Projectiles[i]._xPosition, player2Projectiles[i]._yPosition, Orange);
                explosions.push_back(exp);
                player2Projectiles.erase(player2Projectiles.begin() + i);
                reset();
            }
            if(player2Projectiles[i].TerrainCollision(myTerrain.points))
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
    if(player1Projectiles.size() != 0 || player2Projectiles.size() != 0)
    {
        glutPostRedisplay();
        return;
    }

    // process keypresses
    switch ( key )
    {
        // Move tank left
        case GLUT_KEY_LEFT:
            if(PlayerTurn == 1)
                player1.MoveLeft(myTerrain.points);
            else
                player2.MoveLeft(myTerrain.points);
            break;

        // Move tank right
        case GLUT_KEY_RIGHT:
            if(PlayerTurn == 1)
                player1.MoveRight(myTerrain.points);
            else
                player2.MoveRight(myTerrain.points);
            break;

        // Increase the angle
        case GLUT_KEY_UP:
            if(PlayerTurn == 1)
                player1.ChangeAngle(1);
            else
                player2.ChangeAngle(1);
            break;

        // Decrease the angle
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
    if(player1Projectiles.size() != 0 || player2Projectiles.size() != 0)
    {
        glutPostRedisplay();
        return;
    }

    // process keypresses
    switch ( key )
    {
        // Escape quits program
        case EscapeKey:
            exit( 0 );
            break;
        
        // Spacebar shoots depending on who's turn it is
        case 32:
        {
            if(PlayerTurn == 1)
            {            
                Projectile proj(player1._xPosition + 9, player1._yPosition - 3, player1._velocity, player1._angle, Black);
                player1Projectiles.push_back(proj);
                PlayerTurn = 2;
            }
            else
            {
                Projectile proj(player2._xPosition + 9, player2._yPosition - 3, player2._velocity, player2._angle, Black);
                player2Projectiles.push_back(proj);
                PlayerTurn = 1;
            }
            glutPostRedisplay();
            break;
        }

        // + increases the velocity
        case 43:
            if(PlayerTurn == 1)
                player1.ChangeVelocity(1);
            else
                player2.ChangeVelocity(1);
            break;

        // - decreases the velocity
        case 45:
            if(PlayerTurn == 1)
                player1.ChangeVelocity(-1);
            else
                player2.ChangeVelocity(-1);
            break;

        default:
            glutPostRedisplay();
            break;
    }
}

void reset()
{
    ScreenWidth = 800;
    ScreenHeight = 600;
    PlayerTurn = 1;

    player1Projectiles.clear();
    player2Projectiles.clear();

    myTerrain.Reset();
    
    player1Point = (int)dist(mt);
    player2Point = (int)dist(mt);

    player1._xPosition = myTerrain.points[player1Point].x;
    player1._yPosition = myTerrain.points[player1Point].y;
    player1._angle = 300;
    player1._velocity = 50;

    player2._xPosition = myTerrain.points[myTerrain.points.size() - player2Point].x;
    player2._yPosition = myTerrain.points[myTerrain.points.size() - player2Point].y;
    player2._angle = 240;
    player2._velocity = 50;
}
