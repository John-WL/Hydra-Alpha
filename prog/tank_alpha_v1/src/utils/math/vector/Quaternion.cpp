// Author: John-William Lebel, 2021-04-13, creation

#include "Quaternion.h"
#include "Vector3.h"

Quaternion Quaternion::operator*(Quaternion that)
{
    return Quaternion{
        r*that.r - i*that.i - j*that.j - k*that.k,
        r*that.i + i*that.r + j*that.k - k*that.j,
        r*that.j + j*that.r + k*that.i - i*that.k,
        r*that.k + k*that.r + i*that.j - j*that.i
    };
}

Quaternion Quaternion::operator*(float scalar)
{
    return Quaternion{r*scalar, i*scalar, j*scalar, k*scalar};
}

Vector3 Quaternion::toVector3()
{
    return Vector3{i, j, k};
}