#include "Terrain.h"

int points [5][2] = { {0, 400}, {250, 400}, {400, 150}, {550, 400}, {800, 400} };

void Terrain::DrawTerrain()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    glColor3f(0.0, 0.4, 0.2);

    glBegin( GL_LINE_STRIP );
        glVertex2iv(points[0]);
        glVertex2iv(points[1]);
        glVertex2iv(points[2]);
        glVertex2iv(points[3]);
        glVertex2iv(points[4]);
    glEnd();

    glFlush();
}

void Terrain::DisplaceTerrain()
{
    //Use midpoint displacement
}
