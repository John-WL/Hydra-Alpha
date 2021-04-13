// Author: John-William Lebel, 2021-04-13, creation

#include "ServoMotor.h"

#include "../../../peripheral/i2c/pca9685/Pca9685.h"

ServoMotor::ServoMotor(unsigned char channelNumber) : 
    _channelNumber{channelNumber}, 
    _motorAngle{0}, 
    _previousMotorAngle{0}
{}

void ServoMotor::update()
{
    // don't update for no reason
    if(_motorAngle == _previousMotorAngle) return;

    // Linear function to fit the driver's required range of values.
    // We are indeed using radians for servo motor angles. 
    float shiftedNormalizedAngle = 0.5 + (_motorAngle * ONE_OVER_PI);
    long registerValuesForDriver = SERVO_MOTOR_MIN_VALUE_FOR_PCA9685
        + SERVO_MOTOR_ANGLE_VALUE_RANGE_SIZE * shiftedNormalizedAngle;
    
    Pca9685::update(registerValuesForDriver, _channelNumber);

    // Update the previous state so we can know if "_motorAngle" changed
    // next time this function is called.
    _previousMotorAngle = _motorAngle;
}

float ServoMotor::getMotorAngle()
{
    return _motorAngle;
}

void ServoMotor::setMotorAngle(float desiredMotorAngle)
{
    _motorAngle = desiredMotorAngle;
    if(desiredMotorAngle > PI)
    {
        _motorAngle = PI;
    }
    else if(desiredMotorAngle < -PI)
    {
        _motorAngle = -PI;
    }
}