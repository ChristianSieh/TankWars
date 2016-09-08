#include "Terrain.h"

struct point
{
    GLint x;
    GLint y;
};

vector<point> points = { {0, 400}, {250, 400}, {400, 150}, {550, 400}, {800, 400} };

void Terrain::DrawTerrain()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glEnable(GL_MULTISAMPLE);

    glColor3f(0.0, 0.4, 0.2);

    glBegin( GL_LINE_STRIP );
        for(int i = 0; i < points.size(); i++)
        {
            glVertex2i(points[i].x, points[i].y);
        }
    glEnd();

    glFlush();
}

void Terrain::DisplaceTerrain(int iterations, int roughness)
{
    srand(time(0));

    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < points.size() - 1; j+=2)
        {
            int r = rand() % (2 * roughness + 1) - roughness;
            cout << "Displacement: " << r << endl;
            point midDisplace;
            midDisplace.x =  (points[j].x + points[j + 1].x) * 0.5;
            midDisplace.y = (0.5 * (points[j].y + points[j + 1].y)) + r;

            points.insert(points.begin() + j + 1, midDisplace);
        }

        roughness *= 0.5;
    }
}
