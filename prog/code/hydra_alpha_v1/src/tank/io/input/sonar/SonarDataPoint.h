#ifndef SONAR_DATA_POINT
#define SONAR_DATA_POINT

#include "Arduino.h"

class SonarDataPoint
{
public:
    uint32_t timestamp;
    uint32_t distance;
    float sonarAngle;

private:

};

#endif