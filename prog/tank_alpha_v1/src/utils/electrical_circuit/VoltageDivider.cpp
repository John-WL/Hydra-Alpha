// Author: John-William Lebel, 2021-04-10, creation

#include "VoltageDivider.h"

inline constexpr float VoltageDivider::getVoltageFactor(float r1, float r2)
{
    return r2/(r1+r2);
}

inline constexpr float VoltageDivider::getInverseVoltageFactor(float r1, float r2)
{
    return (r2+r1)/r2;
}
        