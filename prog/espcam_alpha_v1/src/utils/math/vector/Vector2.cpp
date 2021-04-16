// Author: John-William Lebel, 2021-04-13, creation

#include "Vector2.h"

#include "Arduino.h"

Vector2::Vector2() :
    x{0},
    y{0}
{}

Vector2::Vector2(float initialX, float initialY) : 
    x{initialX},
    y{initialY}
{}

Vector2 Vector2::operator*(float scalar)
{
    return Vector2{x*scalar, y*scalar};
}

Vector2 Vector2::operator+(Vector2 that)
{
    return Vector2{x+that.x, y+that.y};
}

Vector2 Vector2::operator-(Vector2 that)
{
    return Vector2{x-that.x, y-that.y};
}

float Vector2::magnitudeSquared()
{
    return x*x + y*y;
}

float Vector2::magnitude()
{
    return sqrt(magnitudeSquared());
}

Vector2 Vector2::normalize()
{
    float calculatedMagnitude = magnitude();
    if(calculatedMagnitude == 0)
    {
        // returning an arbitrary default vector in the X direction
        return Vector2{1, 0};
    }
    return (*this) * (1/calculatedMagnitude);
}

Vector2 Vector2::scaledToMagnitude(float magnitude)
{
    return normalize()*magnitude;
}
