#include "Tank.h"

Tank::Tank(int xPosition, int yPosition, const float* color, int angle)
{
    _xPosition = xPosition;
    _yPosition = yPosition;
    _color = color;
    _angle = angle;
}

void Tank::DrawTank()
{
    glColor3fv( _color );
    glRectf( _xPosition, _yPosition, _xPosition + 12, _yPosition + 8 );
    glRectf( _xPosition + 3, _yPosition, _xPosition + 9, _yPosition - 4);
    glRectf( _xPosition + 4, _yPosition - 1, _xPosition + 15, _yPosition - 3);
    glFlush();
}

void Tank::MoveLeft(vector<Point> points)
{
    int tempX = _xPosition - 5;

    int i = 0;
    
    //cout << "_xPosition: " << _xPosition << " Points[i].x: " << points[i].x << endl;

    while(points[i].x < tempX)
    {
        i++;
    }

    float slope = -((points[i - 1].y - points[i].y) / (points[i - 1].x - points[i].x));

    float b = points[i].y - (slope * points[i].x);

    //cout << "points[i-1].x: " << points[i - 1].x << " points[i].x: " << points[i].x << endl;
    //cout << "points[i-1].y: " << points[i - 1].y << " points[i].y: " << points[i].y << endl;
    //cout << "xPosition: " << _xPosition << " slope: " << slope << " b: " << b <<endl;
    _xPosition = tempX;
    _yPosition = (slope * _xPosition) + b;
    //cout << "yPosition: " << _yPosition << endl;
}

void Tank::MoveRight(vector<Point> points)
{
    int tempX = _xPosition + 5;

    int i = 0;
    
    //cout << "_xPosition: " << _xPosition << " Points[i].x: " << points[i].x << endl;

    while(points[i].x < tempX)
    {
        i++;
    }

    float slope = -((points[i - 1].y - points[i].y) / (points[i - 1].x - points[i].x));

    float b = points[i].y - (slope * points[i].x);

    //cout << "points[i-1].x: " << points[i - 1].x << " points[i].x: " << points[i].x << endl;
    //cout << "points[i-1].y: " << points[i - 1].y << " points[i].y: " << points[i].y << endl;
    //cout << "xPosition: " << _xPosition << " slope: " << slope << " b: " << b <<endl;
    _xPosition = tempX;
    _yPosition = (slope * _xPosition) + b;
    //cout << "yPosition: " << _yPosition << endl;
}
