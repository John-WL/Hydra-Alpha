#include "PidController.h"

PidController::PidController(float kp, float ki, float kd) :
    _kp{kp},
    _ki{ki},
    _kd{kd},
    _previousError{0},
    _errorIntegral{0}
{}

float PidController::compute(float error)
{
    _errorIntegral += error*_ki;
    if(_errorIntegral > ERROR_INTEGRAL_MAX_RANGE)
    {
        _errorIntegral = ERROR_INTEGRAL_MAX_RANGE;
    }
    else if(_errorIntegral < -ERROR_INTEGRAL_MAX_RANGE)
    {
        _errorIntegral = -ERROR_INTEGRAL_MAX_RANGE;
    }
    
    float result =
        error*_kp
        + _errorIntegral
        + (_previousError - error)*_kd;

    _previousError = error;
    return result;
}