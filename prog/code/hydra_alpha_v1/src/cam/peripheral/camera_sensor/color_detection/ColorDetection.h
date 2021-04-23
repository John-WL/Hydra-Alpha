

#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H

#include "arduino.h"

#include "Vector.h"

#include "../../../../shared/utils/math/shape/Rectangle2.h"

#include "../../../../../config/CustomTankDetectionColorValidation.h"

namespace ColorDetection
{
    inline bool testPixel(unsigned int color565)
    {
        return validateColor565(color565);
    }

    std::vector<Rectangle2> generateRectanglesFrom565Buffer(unsigned int* buffer, unsigned char width, unsigned char height)
    {
        unsigned long averageX = 0;
        unsigned long averageY = 0;
        unsigned long validPixelCount = 0;
        for(unsigned long y = 0; y < height; y++)
        {
            for(unsigned long x = 0; x < width; x++)
            {
                if(testPixel(buffer[x * y]))
                {
                    averageX += x;
                    averageY += y;
                    validPixelCount++;
                }
            }
        }

        if(validPixelCount == 0)
        {
            return std::vector<Rectangle2>{};
        }

        Vector2 rectangleCenter = Vector2
        {
            averageX / validPixelCount, 
            averageY / validPixelCount
        };

        float squareSideLength = sqrt(validPixelCount);
        float halfSideLength = squareSideLength/2;

        Vector2 upperLeft = rectangleCenter - Vector2{halfSideLength, halfSideLength};
        Vector2 lowerRight = rectangleCenter + Vector2{halfSideLength, halfSideLength};

        if(upperLeft.x < 0)
        {
            upperLeft.x = 0;
        }
        if(upperLeft.y < 0)
        {
            upperLeft.y = 0;
        }
        if(lowerRight.x > 320)
        {
            lowerRight.x = 320;
        }
        if(lowerRight.y > 240)
        {
            lowerRight.y = 240;
        }

        return Rectangle2{upperLeft, lowerRight};
    }
}

#endif