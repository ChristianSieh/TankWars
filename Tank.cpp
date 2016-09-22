#include "Tank.h"

/*
    Author: Christian Sieh

    Description: Constructor for the tank to set up initial values.

    TODO: Fix player starting position since it's a little wonky
*/
Tank::Tank(int xPosition, int yPosition, const float* color, int angle)
{
    _xPosition = xPosition;
    _yPosition = yPosition;
    _color = color;
    _angle = angle;
    _velocity = 50;
}

/*
    Author: Christian Sieh

    Description: This method draws the 3 pieces of our tank.
*/
void Tank::DrawTank()
{
    glColor3fv( _color );
    //Draw base
    glRectf( _xPosition - 6, _yPosition, _xPosition + 6, _yPosition + 8 );
    //Draw turret
    glRectf( _xPosition - 3, _yPosition, _xPosition + 3, _yPosition - 4);
    //Draw barrel
    glRectf( _xPosition - 2, _yPosition - 1, _xPosition + 9, _yPosition - 3);
    glFlush();
}

/*
    Author: Christian Sieh

    Description: This method allows our tank to move left.
*/
void Tank::MoveLeft(vector<Point> points)
{
    int tempX = _xPosition - 1;

    int i = 0;

    // Get the point to the right of our tank
    while(points[i].x < tempX)
    {
        i++;
    }

    // Use the point to the left and the point to the right of our tank to get the slope
    float slope = (float)(points[i - 1].y - points[i].y) / (float)(points[i - 1].x - points[i].x);

    // Then get the intercept
    float b = points[i].y - (slope * points[i].x);

    // Use the intercept to get our new y position
    // The ( - 8) for y is to make the tank place it's point on the bottom instead
    // of the top left corner
    _xPosition = tempX;
    _yPosition = ((slope * _xPosition) + b) - 8;
}

/*
    Author: Christian Sieh

    Description: This method allows our tank to move right.
*/
void Tank::MoveRight(vector<Point> points)
{
    int tempX = _xPosition + 1;

    int i = 0;

    // Get the point to the right of our tank
    while(points[i].x < tempX)
    {
        i++;
    }

    // Use the point to the left and the point to the right of our tank to get the slope
    float slope = (float)(points[i - 1].y - points[i].y) / (float)(points[i - 1].x - points[i].x);

    // Then get the intercept
    float b = points[i].y - (slope * points[i].x);

    // Use the intercept to get our new y position
    // The ( - 8) for y is to make the tank place it's point on the bottom instead
    // of the top left corner
    _xPosition = tempX;
    _yPosition = ((slope * _xPosition) + b) - 8;
}

/*
    Author: Christian Sieh

    Description: This method just updates the firing angle and makes
                 sure it's between 0-360
*/
void Tank::ChangeAngle(int angle)
{
    _angle += angle;
    _angle = _angle % 360;
}

/*
    Author: Christian Sieh

    Description: This method just updates the velocity for the tank.
*/
void Tank::ChangeVelocity(int velocity)
{
    _velocity += velocity;
}
