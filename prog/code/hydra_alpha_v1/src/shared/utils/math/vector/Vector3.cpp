// Author: John-William Lebel, 2021-04-13, creation

#include "Vector3.h"
#include "Quaternion.h"

#include "Vector2.h"

#include "Arduino.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

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

Vector3::Vector3(imu::Vector<3> adafruitVector) : 
    x{adafruitVector.x()},
    y{adafruitVector.y()},
    z{adafruitVector.z()}
{}

Vector3::Vector3(sensors_event_t adafruitSensor) : 
    x{(360 - adafruitSensor.orientation.z)*PI/180},
    y{(adafruitSensor.orientation.y)*PI/180},
    z{(adafruitSensor.orientation.x)*PI/180}
{}

Vector3 Vector3::operator=(Vector3 that)
{
    x = that.x;
    y = that.y;
    z = that.z;
}

Vector3 Vector3::operator*(float scalar)
{
    return Vector3{x*scalar, y*scalar, z*scalar};
}

Vector3 Vector3::operator+(Vector3 that)
{
    return Vector3{x+that.x, y+that.y, z+that.z};
}

Vector3 Vector3::operator-(Vector3 that)
{
    return Vector3{x-that.x, y-that.y, z-that.z};
}

Vector3 Vector3::rotate(Vector3 rotator)
{
    float a = rotator.magnitude()*0.5;
    float cosa = cos(a);
    Vector3 scaledRotator = rotator.scaledToMagnitude(sin(a));
    Quaternion quaternionRotator{cosa, scaledRotator.x, scaledRotator.y, scaledRotator.z};
    Quaternion conjugateQuaternionRotator{cosa, -scaledRotator.x, -scaledRotator.y, -scaledRotator.z};
    Quaternion result = Quaternion{0, x, y, z} * conjugateQuaternionRotator;
    result = quaternionRotator * result;
    return Vector3{result.i, result.j, result.k};
}

Vector3 Vector3::findRotator(Vector3 rotated)
{
    float differenceMagnitudeSquared = ((*this) - rotated).magnitudeSquared();
    if(differenceMagnitudeSquared < 0.0001)
    {
        return Vector3{};
    }
    return crossProduct(rotated)
        .scaledToMagnitude(angle(rotated));
}

float Vector3::angle(Vector3 other)
{
    float mag2 = (*this).magnitudeSquared();
    float otherMag2 = other.magnitudeSquared();
    float dot = (*this).dotProduct(other);
    return acos(dot / sqrt(mag2 * otherMag2));
}

Vector3 Vector3::normalize()
{
    float calculatedMagnitude = magnitude();
    if(calculatedMagnitude == 0)
    {
        // returning an arbitrary default vector in the X direction
        return Vector3{1, 0, 0};
    }
    return (*this) * (1/calculatedMagnitude);
}

Vector3 Vector3::scaledToMagnitude(float magnitude)
{
    return normalize()*magnitude;
}

Vector3 Vector3::crossProduct(Vector3 other)
{
    float tx = y*other.z - z*other.y;
    float ty = z*other.x - x*other.z;
    float tz = x*other.y - y*other.x;
    return Vector3{tx, ty, tz};
}

float Vector3::dotProduct(Vector3 other)
{
    return x*other.x + y*other.y + z*other.z;
}

float Vector3::magnitude()
{
    return sqrt(magnitudeSquared());
}

float Vector3::magnitudeSquared()
{
    return x*x + y*y + z*z;
}

Vector2 Vector3::flatten()
{
    return Vector2{x, y};
}