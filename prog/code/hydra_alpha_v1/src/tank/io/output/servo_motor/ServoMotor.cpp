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

ServoMotor::ServoMotor(unsigned char channelNumber,
    unsigned int minServoValueForPca9685,
    unsigned int maxServoValueForPca9685) : 
        _channelNumber{channelNumber}, 
        _minServoValueForPca9685{minServoValueForPca9685},
        _servoValueRangeForPca9685{maxServoValueForPca9685 - minServoValueForPca9685},
        _motorAngle{0},
        _previousRegisterValues{0},
        _smoothController{0.2} // should have a value between 0 and 1 for the context of this class...
{}

ServoMotor::ServoMotor(unsigned char channelNumber) :
        _channelNumber{channelNumber},
        _minServoValueForPca9685{SERVO_MOTOR_MIN_VALUE_FOR_PCA9685},
        _servoValueRangeForPca9685{SERVO_MOTOR_ANGLE_VALUE_RANGE_SIZE},
        _motorAngle{0},
        _previousRegisterValues{0},
        _smoothController{1} // should have a value between 0 and 1 for the context of this class...
{}

void ServoMotor::update()
{
    // Linear function to fit the driver's required range of values.
    // We are indeed using radians for the servo motor angles. 
    float shiftedNormalizedAngle = 0.5 + (_motorAngle * ONE_OVER_PI);
    float smoothedAngleValue = _smoothController.sample(shiftedNormalizedAngle);
    uint16_t registerValuesForDriver = _minServoValueForPca9685
        + (_servoValueRangeForPca9685 * smoothedAngleValue);

    // don't update for no reason
    if(registerValuesForDriver == _previousRegisterValues) return;
    
    _servoDriver.setPWM(_channelNumber, 0, registerValuesForDriver);

    // Update the previous state so we can know if "_motorAngle" changed
    // next time this function is called.
    _previousRegisterValues = registerValuesForDriver;
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