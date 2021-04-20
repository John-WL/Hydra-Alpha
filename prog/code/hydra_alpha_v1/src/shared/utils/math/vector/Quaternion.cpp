// Author: John-William Lebel, 2021-04-13, creation

#include "Quaternion.h"
#include "Vector3.h"

Quaternion::Quaternion() :
    r{0},
    i{0},
    j{0},
    k{0}
{}

Quaternion::Quaternion(float initialR, float initialI, float initialJ, float initialK) :
    r{initialR},
    i{initialI},
    j{initialJ},
    k{initialK}
{}

Quaternion Quaternion::operator*(Quaternion other)
{
    return Quaternion
    {
        r*other.r - i*other.i - j*other.j - k*other.k,
        r*other.i + i*other.r + j*other.k - k*other.j,
        r*other.j + j*other.r + k*other.i - i*other.k,
        r*other.k + k*other.r + i*other.j - j*other.i
    };
}

Quaternion Quaternion::operator*=(Quaternion that)
{
    return (*this)*(that);
}

Quaternion Quaternion::operator*(float scalar)
{
    return Quaternion{r*scalar, i*scalar, j*scalar, k*scalar};
}