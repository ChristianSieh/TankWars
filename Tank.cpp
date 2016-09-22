#include "Tank.h"

Tank::Tank(int xPosition, int yPosition, const float* color, int angle)
{
    _xPosition = xPosition;
    _yPosition = yPosition;
    _color = color;
    _angle = angle;
    _velocity = 50;
}

void Tank::DrawTank()
{
    glColor3fv( _color );
    //Draw base
    glRectf( _xPosition - 6, _yPosition, _xPosition + 6, _yPosition + 8 );
    //Draw turret
    glRectf( _xPosition - 3, _yPosition, _xPosition + 3, _yPosition - 4);
    //Draw barrel
    glRectf( _xPosition - 2, _yPosition - 1, _xPosition + 9, _yPosition - 3);
    glFlush();
}

void Tank::MoveLeft(vector<Point> points)
{
    int tempX = _xPosition - 1;

    int i = 0;

    while(points[i].x < tempX)
    {
        i++;
    }

    float slope = (float)(points[i - 1].y - points[i].y) / (float)(points[i - 1].x - points[i].x);

    float b = points[i].y - (slope * points[i].x);

    _xPosition = tempX;
    _yPosition = ((slope * _xPosition) + b) - 8;
}

void Tank::MoveRight(vector<Point> points)
{
    int tempX = _xPosition + 1;

    int i = 0;

    while(points[i].x < tempX)
    {
        i++;
    }

    float slope = (float)(points[i - 1].y - points[i].y) / (float)(points[i - 1].x - points[i].x);

    float b = points[i].y - (slope * points[i].x);

    _xPosition = tempX;
    _yPosition = ((slope * _xPosition) + b) - 8;
}

/*void Tank::Fire()
{
    for(int time = 0; time < 100; time++)
    {
        float x = _velocity * time * cos(_angle * M_PI / 180.0) + _xPosition;
        float y = _velocity * time * sin(_angle * M_PI / 180.0) - ((-9.81 * time * time) / 2) + _yPosition;
        _projectile.DrawProjectile(x, y);
    }
}*/

void Tank::ChangeAngle(int angle)
{
    _angle += angle;
    _angle = _angle % 360;
}

void Tank::ChangeVelocity(int velocity)
{
    _velocity += velocity;
}
