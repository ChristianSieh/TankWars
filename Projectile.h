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
        float _time;

    public:
        int _xPosition;
        int _yPosition;
        int _xOriginalPosition;
        int _yOriginalPosition;
        Projectile(int x, int y, int velocity, int angle);
        void DrawProjectile();
};

#endif
