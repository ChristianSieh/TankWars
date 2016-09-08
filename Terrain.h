#include <GL/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

class Terrain
{
    public:
        static void DrawTerrain();
        void DisplaceTerrain(int iterations, int roughness);
};
