#include "Terrain.h"

void Terrain::DrawTerrain(void)
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    glColor3f(0.0, 0.4, 0.2);

    glBegin( GL_LINE_STRIP );
        glVertex2f( 0, 400 );
        glVertex2f( 250,  400 );
        glVertex2f( 400, 150 );
        glVertex2f(  550,  400 );
        glVertex2f(  800, 400 );
    glEnd();

    glFlush();
}

void Terrain::DisplaceTerrain()
{
    
}
