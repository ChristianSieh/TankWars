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

void Tank::MoveLeft()
{
    _xPosition -= 5;
}

void Tank::MoveRight()
{
    _xPosition += 5;
}
