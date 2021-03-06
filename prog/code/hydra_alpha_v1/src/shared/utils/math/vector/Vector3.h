// Author: John-William Lebel, 2021-04-13, creation

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Vector3
{
    public:
        Vector3();
        Vector3(float x, float y, float z);
        Vector3(imu::Vector<3> adafruitVector);
        Vector3(sensors_event_t adafruitSensor);
        Vector3 operator=(Vector3 that);
        Vector3 operator*(float scalar);
        Vector3 operator+(Vector3 that);
        Vector3 operator-(Vector3 that);
        Vector3 rotate(Vector3 rotator);
        Vector3 findRotator(Vector3 rotated);
        float angle(Vector3 other);
        Vector3 normalize();
        Vector3 scaledToMagnitude(float magnitude);
        Vector3 crossProduct(Vector3 other);
        float dotProduct(Vector3 other);
        float magnitude();
        float magnitudeSquared();
        Vector2 flatten();

        float x;
        float y;
        float z;

    private:

};

#endif