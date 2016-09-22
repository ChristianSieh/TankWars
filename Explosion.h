#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

using namespace std;

class Explosion
{
    private:
        int _radius;
        int _xPosition;
        int _yPosition;
        const float* _color;

    public:
        int _lifeTime;
        Explosion(int x, int y, const float* color);
        void DrawExplosion();
};

#endif
