// Author: John-William Lebel, 2021-04-13, creation

#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
    public:
        Quaternion();
        Quaternion(float r, float i, float j, float k);
        float r;
        float i;
        float j;
        float k;

        Quaternion operator*(Quaternion that);
        Quaternion operator*(float scalar);
        Vector3 toVector3();

    private:

};

#endif