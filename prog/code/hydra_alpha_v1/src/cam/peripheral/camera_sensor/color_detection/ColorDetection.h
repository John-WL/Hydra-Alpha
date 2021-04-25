

#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H

#include "arduino.h"

#include "Vector.h"

#include "../../../../shared/utils/math/shape/Rectangle2.h"

#include "../../../../../config/CustomTankDetectionColorValidation.h"

namespace ColorDetection
{
    std::vector<Rectangle2> generateRectanglesFrom565Buffer(unsigned int* buffer, unsigned int width, unsigned int height)
    {
        std::vector<Rectangle2> result{};

        unsigned long averageX = 0;
        unsigned long averageY = 0;
        unsigned long validPixelCount = 0;
        for(unsigned long y = 0; y < height; y++)
        {
            for(unsigned long x = 0; x < width; x++)
            {
                if(validateColor565(buffer[x + (y * width)]))
                {
                    averageX += x;
                    averageY += y;
                    validPixelCount++;
                }
            }
        }

        if(validPixelCount == 0)
        {
            return result;
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
        if(lowerRight.x > width)
        {
            lowerRight.x = width;
        }
        if(lowerRight.y > height)
        {
            lowerRight.y = height;
        }
        result.push_back(Rectangle2{upperLeft, lowerRight});

        return result;
    }
}

#endif
