#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

using namespace std;

class Projectile
{
    private:
        int _xPosition;
        int _yPosition;

    public:
        void DrawProjectile(float x, float y);
};
