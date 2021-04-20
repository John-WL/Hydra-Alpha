// Author: John-William Lebel, 2021-04-15, creation

#ifndef RECTANGLE2_H
#define RECTANGLE2_H

#include "../vector/Vector2.h"

class Rectangle2
{
    public:
        Rectangle2(Vector2 upperLeft, Vector2 lowerRight);
        Vector2 findCenter();
        float diagonalSizeSquared();
        float diagonalSize();

        Vector2 upperLeft;
        Vector2 lowerRight;

    private:

};

#endif