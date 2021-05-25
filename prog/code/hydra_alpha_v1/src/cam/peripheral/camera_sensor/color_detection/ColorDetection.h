

#ifndef COLOR_DETECTION_H
#define COLOR_DETECTION_H

#include "Arduino.h"

#include "Vector.h"

#include "../../../../shared/utils/math/shape/Rectangle2.h"

#include "../../../../../config/CustomTankDetectionColorValidation.h"

namespace ColorDetection
{
    void generateRectanglesFrom565Buffer(
        uint16_t* buffer,
        unsigned int width,
        unsigned int height,
        std::vector<Rectangle2>* detectedRectangle)
    {
        unsigned long averageX = 0;
        unsigned long averageY = 0;
        unsigned long validPixelCount = 0;
        unsigned long x, y;

        for(y = 0; y < height; y++)
        {
            for(x = 0; x < width; x++)
            {
                if(validateColor565(buffer[x + (y * width)]))
                {
                    averageX += x;
                    averageY += y;
                    validPixelCount++;

                    buffer[x + (y * width)] = 0b1111100000000000;
                }
            }
        }

        if(validPixelCount == 0)
        {
            return;
        }

        Vector2 rectangleCenter = Vector2
        {
            averageX / validPixelCount, 
            averageY / validPixelCount
        };

        Serial.print("X: ");
        Serial.println(rectangleCenter.x);
        Serial.print("Y: ");
        Serial.println(rectangleCenter.y);
        Serial.println("");

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
        
        detectedRectangle->push_back(Rectangle2{upperLeft, lowerRight});
    }
}

#endif
