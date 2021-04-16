// Author: John-William Lebel, 2021-04-13, creation

#include "Vector3.h"
#include "Quaternion.h"

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
    x{adafruitSensor.orientation.x},
    y{adafruitSensor.orientation.y},
    z{adafruitSensor.orientation.z}
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

// unimplemented lol
Vector3 Vector3::findRotator(Vector3 rotated)
{
    return Vector3{};
}