// Author: John-William Lebel, 2021-04-15, creation

#include "Rectangle2.h"

#include "../vector/Vector3.h"

Rectangle2::Rectangle2(Vector2 initialUpperLeft, Vector2 initialLowerRight) :
    upperLeft{initialUpperLeft},
    lowerRight{initialLowerRight}
{}

Vector2 Rectangle2::findCenter()
{
    return (upperLeft + lowerRight) * 0.5;
}

float Rectangle2::diagonalSizeSquared()
{
    return (upperLeft - lowerRight).magnitudeSquared();
}

float Rectangle2::diagonalSize()
{
    return sqrt(diagonalSizeSquared());
}