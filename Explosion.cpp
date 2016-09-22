#include "Explosion.h"

Explosion::Explosion(int x, int y, const float* color)
{
    _xPosition = x;
    _yPosition = y;
    _color = color;
    _lifeTime = 5;
    _radius = 10;
}

void Explosion::DrawExplosion()
{
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
}
