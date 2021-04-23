

#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H

#include "../../../../config/CustomTankDetectionColorValidation.h"

namespace ColorDetection
{
    inline bool test(unsigned int color565)
    {
        return validateColor565(color565);
    }
}

#endif