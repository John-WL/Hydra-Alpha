// Author: John-William Lebel, 2021-04-13, creation

#ifndef ORIENTATION3_H
#define ORIENTATION3_H

#include "Vector3.h"

class Orientation3
{
    public:
        Orientation3();
        Orientation3(Vector3 front, Vector3 roof);
        Vector3 front;
        Vector3 roof;

    private:

};

#endif