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

BdcMotor::BdcMotor(uint8_t channelNumber, uint8_t pwmPinNumber, float* bdcPwmValues) :
    _channelNumber{channelNumber},
    _pwmPinNumber{pwmPinNumber},
    _motorTorque{0},
    _pulseController{}
{
    pinMode(pwmPinNumber, OUTPUT);
    digitalWrite(pwmPinNumber, LOW);
    _bdcPwmValues = bdcPwmValues;
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
    uint8_t torqueIndex{4};
    if(desiredMotorTorque > 0.2)
    {
        torqueIndex = ((desiredMotorTorque + 1) * 4) + 0.5;
    }
    else if(desiredMotorTorque < -0.2)
    {
        torqueIndex = ((desiredMotorTorque + 1) * 4) + 0.5;
    }

    if(torqueIndex > 8)
    {
        torqueIndex = 0;
    }
    _motorTorque = _bdcPwmValues[torqueIndex];

    Serial.println(_bdcPwmValues[torqueIndex]);
}
