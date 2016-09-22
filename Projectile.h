#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include "Tank.h"
#include "Terrain.h"

using namespace std;

class Projectile
{
    private:
        int _velocity;
        int _angle;
        float _time;
        int _radius;

    public:
        int _xPosition;
        int _yPosition;
        int _xOriginalPosition;
        int _yOriginalPosition;
        Projectile(int x, int y, int velocity, int angle);
        void DrawProjectile();
        bool TankCollision(Tank player);
        bool TerrainCollision(vector<Point> points);
};

#endif
