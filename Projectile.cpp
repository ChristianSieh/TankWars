#include "Projectile.h"

void Projectile::DrawProjectile(float centerX, float centerY)
{
    int numSegments = 100;

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < numSegments; i++)
    {
        float theta = 2.0 * M_PI * i / numSegments;

        float x = 5 * cosf(theta);
        float y = 5 * sinf(theta);

        glVertex2f(x + centerX, y + centerY);
    }
    glEnd();

    glFlush();
}
