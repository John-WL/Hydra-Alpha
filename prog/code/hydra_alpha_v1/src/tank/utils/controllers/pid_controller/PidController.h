#ifndef PID_CONTROLLER
#define PID_CONTROLLER

#define ERROR_INTEGRAL_MAX_RANGE 10

class PidController
{
public:
    PidController(float kp, float ki, float kd);
    float compute(float error);

private:
    float _kp, _ki, _kd, _previousError, _errorIntegral;

};

#endif