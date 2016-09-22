#include "Projectile.h"

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

void Projectile::DrawProjectile()
{
    _xPosition = _velocity * _time * cos(_angle * M_PI / 180.0) + _xOriginalPosition;
    _yPosition = _velocity * _time * sin(_angle * M_PI / 180.0) - ((-9.81 * _time * _time) / 2) + _yOriginalPosition;

    int numSegments = 100;

    glColor3fv( _color );

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
        || ((_yPosition - _radius) >= player._yPosition && (_yPosition - _radius) <= player._yPosition + 8) ) 
    {
        //cout << "YPosition + radius: " << _yPosition + _radius << " YPosition - radius: " << _yPosition - _radius << endl;
        //cout << "Tank YPosition: " << player._yPosition << " Tank YPosition + 8: " << player._yPosition + 8 << endl;
        //Check that they x value of the projectile is the same as inside the rectangle
        if(((_xPosition + _radius) >= player._xPosition - 6 && (_xPosition + _radius) <= player._xPosition + 6)
            || ((_xPosition - _radius) >= player._xPosition - 6 && (_xPosition - _radius) <= player._xPosition + 6))
        {
            //cout << "XPosition + radius: " << _xPosition + _radius << " XPosition - radius: " << _xPosition - _radius << endl;
            //cout << "Tank XPosition: " << player._xPosition << " Tank XPosition + 8: " << player._xPosition + 8 << endl;
            return true;
        }
    }

    return false;
}

bool Projectile::TerrainCollision(vector<Point> points)
{
    int i = 0;

    while(points[i].x < _xPosition)
    {
        i++;
    }

    float slope = -((points[i - 1].y - points[i].y) / (points[i - 1].x - points[i].x));

    float b = points[i].y - (slope * points[i].x);

    if(_yPosition >= (slope * _xPosition) + b)
        return true;

    return false;
}
