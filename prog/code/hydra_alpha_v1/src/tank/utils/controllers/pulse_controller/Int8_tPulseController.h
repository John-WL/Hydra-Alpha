#ifndef INT8_T_PULSE_CONTROLLER_H
#define INT8_T_PULSE_CONTROLLER_H

#include "Arduino.h"

class Int8_tPulseController
{
public:
    Int8_tPulseController();
    int8_t sample(float desiredValue);

private:
    float _pulseThreshold;

};

#endif