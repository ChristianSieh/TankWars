#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

using namespace std;

class Projectile
{
    private:
        int _velocity;
        int _angle;
        int _time;

    public:
        int _xPosition;
        int _yPosition;
        Projectile(int x, int y, int velocity, int angle);
        void DrawProjectile();
};

#endif
