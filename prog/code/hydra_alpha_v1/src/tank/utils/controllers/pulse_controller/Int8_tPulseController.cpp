#include "Int8_tPulseController.h"

#include "Arduino.h"

Int8_tPulseController::Int8_tPulseController() :
    _pulseThreshold{0}
{}

int8_t Int8_tPulseController::sample(float desiredValue)
{
    int8_t effectiveValue = (int8_t)desiredValue;   // convert to int8_t

    _pulseThreshold += desiredValue - effectiveValue;   // add the decimals (0.xxx)
    if(_pulseThreshold >= 1)    // threshold reached
    {
        effectiveValue++;       // add 1 to account for the error we accumulated
        _pulseThreshold--; // remove 1 because we just put it in the output
    }
    else if(_pulseThreshold <= -1)
    {
        effectiveValue--;       // remove 1 to account for the error we accumulated
        _pulseThreshold++; // add 1 because we just took it from the output
    }

    return effectiveValue;
}