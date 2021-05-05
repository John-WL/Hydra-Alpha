#ifndef SONAR_SAMPLE
#define SONAR_SAMPLE

#include "Arduino.h"

class SonarSample
{
public:
    uint32_t timestamp;
    uint32_t distance;
    float sonarAngle;

private:

};

#endif