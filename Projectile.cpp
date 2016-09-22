#include "Projectile.h"

/*
    Author: Christian Sieh

    Description: This is the constructor for the projectile that the tanks fire.
                 It sets up the initial values of the projectile.
*/
Projectile::Projectile(int x, int y, int velocity, int angle, const float* color)
{
    _xPosition = x;
    _yPosition = y;
    _xOriginalPosition = x;
    _yOriginalPosition = y;
    _velocity = velocity;
    _angle = angle;
    _time = 0;
    _radius = 3;
    _color = color;
}

/*
    Author: Christian Sieh

    Description: This function is used to draw the projectile. 
*/
void Projectile::DrawProjectile()
{
    // We use the original position so we can keep track of our parabola.
    // Otherwise we would be starting a new parabola on each redraw.
    _xPosition = _velocity * _time * cos(_angle * M_PI / 180.0) + _xOriginalPosition;
    _yPosition = _velocity * _time * sin(_angle * M_PI / 180.0) - ((-9.81 * _time * _time) / 2) + _yOriginalPosition;

    glColor3fv( _color );

    int numSegments = 100;

    // This draws us a circle by drawin numSegments amount of lines by
    // using cos and sin with theta to get us our x and y points.
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < numSegments; i++)
    {
        float theta = 2.0 * M_PI * i / numSegments;

        float x = _radius * cosf(theta);
        float y = _radius * sinf(theta);

        glVertex2f(x + _xPosition, y + _yPosition);
    }
    glEnd();

    glFlush();

    // Time is used to keep track of how far the projectile has moved along the parabola
    _time += .1;
}

/*
    Author: Christian Sieh

    Description: This function is used to detect collision between the projectile
                 and a player's tank. 
*/
bool Projectile::TankCollision(Tank player)
{
    //Check that the y value of the projectile is the same as inside the rectangle
    if(((_yPosition + _radius) >= player._yPosition && (_yPosition + _radius) <= player._yPosition + 8)
        || ((_yPosition - _radius) >= player._yPosition && (_yPosition - _radius) <= player._yPosition + 8) ) 
    {
        //Check that they x value of the projectile is the same as inside the rectangle
        if(((_xPosition + _radius) >= player._xPosition - 6 && (_xPosition + _radius) <= player._xPosition + 6)
            || ((_xPosition - _radius) >= player._xPosition - 6 && (_xPosition - _radius) <= player._xPosition + 6))
        {
            return true;
        }
    }

    return false;
}

/*
    Author: Christian Sieh

    Description: This function is used to detect collision between then projectile
                 and a the terrain.
*/
bool Projectile::TerrainCollision(vector<Point> points)
{
    int i = 0;

    // Get the terrain point to the right of the projectile
    while(points[i].x < _xPosition)
    {
        i++;
    }

    // Use the terrain point to the left of the projectile and to the right to get the slope
    float slope = -((points[i - 1].y - points[i].y) / (points[i - 1].x - points[i].x));

    // Then get the intercept
    float b = points[i].y - (slope * points[i].x);

    // If the projectile is below or equal to the terrain then it has collided.
    if(_yPosition >= (slope * _xPosition) + b)
        return true;

    return false;
}
