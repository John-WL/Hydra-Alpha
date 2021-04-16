// Author: John-William Lebel, 2021-04-13, creation

#ifndef ORIENTATION3_H
#define ORIENTATION3_H

#include "Vector3.h"

#define DEFAULT_FRONT_ORIENTATION Vector3{1, 0, 0}
#define DEFAULT_ROOF_ORIENTATION Vector3{0, 0, 1}

class Orientation3
{
    public:
        Orientation3();
        Orientation3(Vector3 front, Vector3 roof);
        Orientation3 operator=(Orientation3 orientation);
        Vector3 front;
        Vector3 roof;

        Orientation3 rotate(Vector3 rotator);

        static Orientation3 eulerXyzToOrientation(Vector3 eulerXyz);

    private:

};

#endif