#include <GL/freeglut.h>
#include <iostream>
#include "Terrain.h"
#include "Point.h"

using namespace std;

class Tank
{
    private:
        int _xPosition;
        int _yPosition;
        int _velocity;
        int _angle;
        const float* _color;
        int _health;
    public:
        Tank(int xPosition, int yPosition, const float* color, int angle);
        void DrawTank();
        void MoveLeft(vector<Point> points);
        void MoveRight(vector<Point> points);
};
