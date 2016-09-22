#include "Projectile.h"

Projectile::Projectile(int x, int y, int velocity, int angle)
{
    _xPosition = x;
    _yPosition = y;
    _xOriginalPosition = x;
    _yOriginalPosition = y;
    _velocity = velocity;
    _angle = angle;
    _time = 0;
    _radius = 3;
}

void Projectile::DrawProjectile()
{
    _xPosition = _velocity * _time * cos(_angle * M_PI / 180.0) + _xOriginalPosition;
    _yPosition = _velocity * _time * sin(_angle * M_PI / 180.0) - ((-9.81 * _time * _time) / 2) + _yOriginalPosition;

    int numSegments = 100;

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

    _time += .1;
}

bool Projectile::TankCollision(Tank player)
{
    //Check that the y value of the projectile is the same as inside the rectangle
    if(((_yPosition + _radius) >= player._yPosition && (_yPosition + _radius) <= player._yPosition + 8)
        || ((_yPosition - _radius) >= player._yPosition && (_yPosition - _radius) <= player._yPosition + 8)) 
    {
        //Check that they x value of the projectile is the same as inside the rectangle
        if(((_xPosition + _radius) >= player._xPosition && (_xPosition + _radius) <= player._xPosition + 12)
            || ((_xPosition - _radius) >= player._xPosition && (_xPosition - _radius) <= player._xPosition + 12))
        {
            return true;
        }
    }

    return false;
}

bool Projectile::TerrainCollision(Terrain myTerrain)
{
    

    return false;
}
