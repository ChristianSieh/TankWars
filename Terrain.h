#include <GL/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

class Terrain
{
    public:
        struct point
        {
            GLint x;
            GLint y;
        };
        vector<point> points;
        Terrain();
        void DrawTerrain();
        void DisplaceTerrain(int iterations, int roughness);
};
