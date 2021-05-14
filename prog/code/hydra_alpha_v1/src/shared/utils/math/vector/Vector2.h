// Author: John-William Lebel, 2021-04-13, creation

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
    public:
        Vector2();
        Vector2(float x, float y);
        Vector2 operator*(float scalar);
        Vector2 operator+(Vector2 that);
        Vector2 operator-(Vector2 that);
        float magnitudeSquared();
        float magnitude();
        Vector2 normalize();
        Vector2 scaledToMagnitude(float magnitude);
        
        float x;
        float y;

    private:

};

#endif