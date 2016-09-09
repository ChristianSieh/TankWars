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

        float x = 5 * cosf(theta);
        float y = 5 * sinf(theta);

        glVertex2f(x + _xPosition, y + _yPosition);
    }
    glEnd();

    glFlush();

    _time += .1;
}
