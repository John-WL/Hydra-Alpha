// Author: John-William Lebel, 2021-04-13, creation

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Quaternion.h"

class Vector3
{
    public:
        Vector3();
        Vector3(float x, float y, float z);
        float x;
        float y;
        float z;

        float magnitudeSquared();
        float magnitude();

        Vector3 normalize();
        Vector3 scaledToMagnitude(float magnitude);
        
        Quaternion toQuaternion();
        Vector3 rotate(Vector3 rotator);
        Vector3 findRotator(Vector3 rotated);

    private:

};

#endif