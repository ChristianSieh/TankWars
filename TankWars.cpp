/*
    Author: Christian Sieh
    Date: 9/22/2016
    Title: TankWars
    Class: Computer Graphics, CSC443, Fall 16
    Professor: Dr. John Weiss
    
    Usage: 
            ./TankWars

    Controls:
            Left Arrow: Move current tank left
            Right Arrow: Move current tank right
            Up Arrow: Increase the firing angle
            Down Arrow: Decrese the firing angle
            +: Increase the firing velocity
            -: Decrease the firing velocity
            Space: Fire projectile
            Escape: Exit program

    Description:
        When the program first launches it uses the Terrain class, the points,
        defined inside, and the midpoint displacement algorithm to make semi
        realistic terrain. Then Player1 and Player2 are randomly placed on the
        left and right sides of the mountains and the game begins.

        The objective of the game is to hit the other players tank with a
        projectile by using the controls listed above. You are only allowed
        to fire and move on your turn and once a player is hit, the game
        resets.

    Note:
        The projectile fires from the end of the player's barrel so make
        sure your barrel is sticking inside the mountain.
    
    TODO:
        Add barrel rotation since currently Player2 is at a disadvantage.

    Extras Added:
            - MSAA to clear up jagged edges
            - Animated projectile
*/

#include <iostream>
#include <GL/freeglut.h>
#include <random>
#include "Terrain.h"
#include "Tank.h"
#include "Projectile.h"

using namespace std;

// Consts
const int EscapeKey = 27;
const float Red[] = { 1.0, 0.0, 0.0 };
const float Blue[] = { 0.0, 0.0, 1.0 };
const float Orange[] = { 1.0, 0.647, 0.0 };
const float Black[] = { 0.0, 0.0, 0.0 };
const float White[] = { 1.0, 1.0, 1.0 };

// Using C++11 to get a random number since it's supposed to be better
random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> dist(3.0, 15.0);
int player1Point = (int)dist(mt);
int player2Point = (int)dist(mt);

// Globals
float ScreenWidth = 800;
float ScreenHeight = 600;
int PlayerTurn = 1;
Terrain myTerrain;
Tank player1(myTerrain.points[player1Point].x, myTerrain.points[player1Point].y, Red, 300);
Tank player2(myTerrain.points[myTerrain.points.size() - player2Point].x, myTerrain.points[myTerrain.points.size() - player2Point].y, Blue, 240);
vector<Projectile> player1Projectiles;
vector<Projectile> player2Projectiles;

// Prototypes
void reset();
void init( void );
void display( void );
void special( int key, int x, int y);
void keyboard( unsigned char key, int x, int y );
void DrawText();
/*
    Author: Christian Sieh
    Original Author: Dr. John Weiss, SDSMT

    Description: The main functions sets up all of our default values as well as
                 glut functions. It then calls glutMainLoop() and stays in there
                 until the program stops running.
*/
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

/*
    Author: Christian Sieh
    Original Author: Dr. John Weiss, SDSMT

    Description: This function is just to initialize some values.
*/
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, ScreenWidth, ScreenHeight, 0.0);
}

/*
    Author: Christian Sieh
    Original Author: Dr. John Weiss, SDSMT

    Description: This function runs all of the draw functions as well as deleting projectiles
                 when they are no longer needed.

    TODO: Pull the projectile part out into a function
*/
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    myTerrain.DrawTerrain();

    player1.DrawTank();
    player2.DrawTank();

    DrawText();

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
            // Check for projectile collision with player2's tank
            if(player1Projectiles[i].TankCollision(player2))
            {
                player1Projectiles.erase(player1Projectiles.begin() + i);
                reset();
            }
            // Check for collision with the ground
            if(player1Projectiles[i].TerrainCollision(myTerrain.points))
            {
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
            
            // Check for projectile collision with player1's tank
            if(player2Projectiles[i].TankCollision(player1))
            {
                player2Projectiles.erase(player2Projectiles.begin() + i);
                reset();
            }
            // Check for collision with the ground
            if(player2Projectiles[i].TerrainCollision(myTerrain.points))
            {
                player2Projectiles.erase(player2Projectiles.begin() + i);
            }
        }
    }

    glutSwapBuffers();
    glFlush();
}

/*
    Author: Christian Sieh
    Original Author: Dr. John Weiss, SDSMT

    Description: This function handles glut special keys such as up, down, left, right.
                 Left and right are used to move the current player's tank and up and
                 down are used to change the firing angle.
*/
void special( int key, int x, int y )
{
    // If there are still projectiles flying around then ignore key presses
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

/*
    Author: Christian Sieh
    Original Author: Dr. John Weiss, SDSMT

    Description: This function is to handle keyboard presses. Escape exits
                 the program, spacebar is for the current player's tank to
                 shoot, - is to decrease velocity, and + is to increase
                 velocity.
*/
void keyboard( unsigned char key, int x, int y )
{
    // If there are still projectiles flying around then ignore key presses
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

/*
    Author: Christian Sieh

    Description: This function is resets everything to a new game once
                 one player has one
*/
void reset()
{
    player1Projectiles.clear();
    player2Projectiles.clear();

    ScreenWidth = 800;
    ScreenHeight = 600;
    PlayerTurn = 1;

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

/*
    Author: Christian Sieh

    Description: This is the draw function to display the velocity and angle
                 of each player's tank
*/
void DrawText()
{
    glColor3fv( Black );
    glMatrixMode(GL_MODELVIEW);

    // Player 1 Velocity
    glPushMatrix();
    glTranslatef( 100, ScreenHeight - 100, 0 );
    glScalef(0.2, -0.2, 0.2);
    string playerVelocity = "Velocity: " + to_string(player1._velocity);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)playerVelocity.c_str());
    glPopMatrix();

    // Player 1 Angle
    glPushMatrix();
    glTranslatef( 100, ScreenHeight - 50, 0 );
    glScalef(0.2, -0.2, 0.2);
    string playerAngle = "Angle: " + to_string(player1._angle);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)playerAngle.c_str());
    glPopMatrix();

    // Player 2 Velocity
    glPushMatrix();
    glTranslatef( ScreenWidth - 250, ScreenHeight - 100, 0 );
    glScalef(0.2, -0.2, 0.2);
    playerVelocity = "Velocity: " + to_string(player2._velocity);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)playerVelocity.c_str());
    glPopMatrix();

    // Player 2 Angle
    glPushMatrix();
    glTranslatef( ScreenWidth - 250, ScreenHeight - 50, 0 );
    glScalef(0.2, -0.2, 0.2);
    playerAngle = "Angle: " + to_string(player2._angle);
    glutStrokeString( GLUT_STROKE_ROMAN, (const unsigned char *)playerAngle.c_str());
    glPopMatrix();

}
