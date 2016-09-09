#ifndef TERRAIN_H
#define TERRAIN_H

#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "Point.h"

using namespace std;

class Terrain
{
    public:
        vector<Point> points;
        Terrain();
        void DrawTerrain();
        void DisplaceTerrain(int iterations, int roughness);
};

#endif
