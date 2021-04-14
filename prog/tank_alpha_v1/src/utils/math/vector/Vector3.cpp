// Author: John-William Lebel, 2021-04-13, creation

#include "Vector3.h"
#include "Quaternion.h"

#include "Arduino.h"

Vector3::Vector3() :
    x{0},
    y{0},
    z{0}
{}

Vector3::Vector3(float initialX, float initialY, float initialZ) : 
    x{initialX},
    y{initialY},
    z{initialZ}
{}

float Vector3::magnitudeSquared()
{
    return x*x + y*y + z*z;
}

float Vector3::magnitude()
{
    return sqrt(magnitudeSquared());
}

Vector3 Vector3::normalize()
{
    return (*this) * (1/magnitude());
}

Vector3 Vector3::scaledToMagnitude(float magnitude)
{
    return normalize()*magnitude;
}

Quaternion Vector3::toQuaternion()
{
    return Quaternion(0, x, y, z);
}

Vector3 Vector3::rotate(Vector3 rotator)
{
    float a = rotator.magnitude()*0.5;
    float cosa = cos(a);
    Vector3 scaledRotator = rotator.scaledToMagnitude(sin(a));
    Quaternion quaternionRotator(cosa, scaledRotator.x, scaledRotator.y, scaledRotator.z);
    Quaternion conjugateQuaternionRotator(cosa, -scaledRotator.x, -scaledRotator.y, -scaledRotator.z);
    return ((quaternionRotator*this->toQuaternion())*conjugateQuaternionRotator).toVector3();
}

Vector3 Vector3::findRotator(Vector3 rotated)
{
    
}