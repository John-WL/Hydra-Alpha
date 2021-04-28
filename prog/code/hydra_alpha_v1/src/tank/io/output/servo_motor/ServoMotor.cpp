// Author: John-William Lebel, 2021-04-13, creation

#include "ServoMotor.h"

#include "../../../utils/controllers/exponential_controller/ExponentialController.h"

#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

void ServoMotor::initI2cCommunication()
{
    _servoDriver.begin();
    _servoDriver.setOscillatorFrequency(23000000);
    _servoDriver.setPWMFreq(50);
}

ServoMotor::ServoMotor(unsigned char channelNumber) : 
    _channelNumber{channelNumber}, 
    _motorAngle{0},
    _previousMotorAngle{0},
    _smoothController{1} // should have a value between 0 and 1 for the context of this class...
    
{}

void ServoMotor::update()
{
    // don't update for no reason
    if(_motorAngle == _previousMotorAngle) return;

    // Linear function to fit the driver's required range of values.
    // We are indeed using radians for servo motor angles. 
    float shiftedNormalizedAngle = 0.5 + (_motorAngle * ONE_OVER_PI);
    uint16_t registerValuesForDriver = SERVO_MOTOR_MIN_VALUE_FOR_PCA9685
        + (SERVO_MOTOR_ANGLE_VALUE_RANGE_SIZE * _smoothController.sample(shiftedNormalizedAngle));
    
    _servoDriver.setPWM(_channelNumber, 0, registerValuesForDriver);

    Serial.println(SERVO_MOTOR_MIN_VALUE_FOR_PCA9685);

    // Update the previous state so we can know if "_motorAngle" changed
    // next time this function is called.
    //_previousMotorAngle = _motorAngle;
}

float ServoMotor::getMotorAngle()
{
    return _motorAngle;
}

void ServoMotor::setMotorAngle(float desiredMotorAngle)
{
    _motorAngle = desiredMotorAngle;
    if(desiredMotorAngle > PI/2)
    {
        _motorAngle = PI/2;
    }
    else if(desiredMotorAngle < -PI/2)
    {
        _motorAngle = -PI/2;
    }
}

Adafruit_PWMServoDriver ServoMotor::_servoDriver{};