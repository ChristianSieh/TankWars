#ifndef TANK_H
#define TANK_H

#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include "Terrain.h"
#include "Point.h"

using namespace std;

class Tank
{
    private:
        const float* _color;
    public:
        int _xPosition;
        int _yPosition;
        int _velocity;
        int _angle;
        Tank(int xPosition, int yPosition, const float* color, int angle);
        void DrawTank();
        void MoveLeft(vector<Point> points);
        void MoveRight(vector<Point> points);
        void Fire();
        void ChangeAngle(int angle);
        void ChangeVelocity(int velocity);
};

#endif
