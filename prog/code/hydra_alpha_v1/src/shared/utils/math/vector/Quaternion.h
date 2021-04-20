// Author: John-William Lebel, 2021-04-13, creation

#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
    public:
        Quaternion();
        Quaternion(float r, float i, float j, float k);
        Quaternion operator*(Quaternion that);
        Quaternion operator*=(Quaternion that);
        Quaternion operator*(float scalar);
        float r;
        float i;
        float j;
        float k;

    private:

};

#endif