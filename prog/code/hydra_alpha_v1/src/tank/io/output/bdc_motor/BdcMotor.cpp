// Author: John-William Lebel, 2021-04-11, creation

#include "BdcMotor.h"

#include "Arduino.h"

#include "../../../peripheral/i2c/xra1201/Xra1201.h"

BdcMotor::BdcMotor(uint8_t channelNumber, uint8_t pwmPinNumber) : 
    _channelNumber{channelNumber},
    _pwmPinNumber{pwmPinNumber},
    _motorTorque{0},
    _pulseController{}
{
    pinMode(pwmPinNumber, OUTPUT);
    digitalWrite(pwmPinNumber, LOW);
}

void BdcMotor::update()
{
    // that part definitely yeilds the expected results
    int8_t motorEnabled = _pulseController.sample(_motorTorque);

    // that part too
    if(motorEnabled != 0)
    {
        digitalWrite(_pwmPinNumber, HIGH);
    }
    else
    {
        digitalWrite(_pwmPinNumber, LOW);
    }

    if(motorEnabled != 0)
    {
        uint8_t bitShiftAmount = _channelNumber * BDC_MOTOR_BITS_PER_CHANNEL;
        if(_motorTorque > 0)
        {
            Xra1201::value |= 0x0020 << bitShiftAmount;
        }
        else
        {
            Xra1201::value &= ~(0x0020 << bitShiftAmount);
        }
    }
}

void BdcMotor::setMotorTorque(float desiredMotorTorque)
{
    _motorTorque = desiredMotorTorque;
    if(desiredMotorTorque > 1)
    {
        _motorTorque = 1;
    }
    else if(desiredMotorTorque < -1)
    {
        _motorTorque = -1;
    }
}
