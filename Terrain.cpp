#include "Terrain.h"

/*
    Author: Christian Sieh

    Description: The constructor sets out our initial points and then uses DisplaceTerrain
                 to add randomness and make it look more realistic
*/
Terrain::Terrain()
{
    points = { {0, 400}, {100, 400}, {250, 400}, {400, 200}, {550, 400}, {700, 400}, {800, 400} };

    DisplaceTerrain(4, 50);
}

/*
    Author: Christian Sieh

    Description: This method draws the terrain by using a line strip and going
                 through each point in the points vector.
*/
void Terrain::DrawTerrain()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    glColor3f(0.0, 0.4, 0.2);

    glBegin( GL_LINE_STRIP );
        for(unsigned int i = 0; i < points.size(); i++)
        {
            glVertex2i(points[i].x, points[i].y);
        }
    glEnd();

    glFlush();
}

/*
    Author: Christian Sieh

    Description: This method is used to add roughness to our terrain by using
                 the midpoint displacement algorithm.
*/
void Terrain::DisplaceTerrain(int iterations, int roughness)
{
    srand(time(0));

    // Run multiple times to add more midpoints and randomness
    for(int i = 0; i < iterations; i++)
    {
        // Create a midpoint for each pair of points in the points vector
        for(unsigned int j = 0; j < points.size() - 1; j+=2)
        {
            int r = rand() % (2 * roughness + 1) - roughness;
            Point midDisplace;
            // X is just the midpoint
            midDisplace.x =  (points[j].x + points[j + 1].x) * 0.5;
            // Y is the midpoint plus the roughness value
            midDisplace.y = (0.5 * (points[j].y + points[j + 1].y)) + r;

            points.insert(points.begin() + j + 1, midDisplace);
        }

        roughness *= 0.5;
    }
}

/*
    Author: Christian Sieh

    Description: This method just resets the initial values of the terrain so we
                 can regenerate it when we start a new game.
*/
void Terrain::Reset()
{
    points = { {0, 400}, {100, 400}, {250, 400}, {400, 200}, {550, 400}, {700, 400}, {800, 400} };

    DisplaceTerrain(4, 50);
}
