// Author: John-William Lebel, 2021-04-11, creation

#include "BdcMotor.h"

#include "Arduino.h"

#include "../../../peripheral/i2c/xra1201/Xra1201.h"

BdcMotor::BdcMotor(unsigned char channelNumber) : 
    _channelNumber{channelNumber},
    _motorTorque{0},
    _pulseController{}
{}

void BdcMotor::update()
{
    int8_t effectiveMotorTorque = _pulseController.sample(_motorTorque);

    uint16_t unsignedMotorTorque = abs(effectiveMotorTorque);
    uint8_t bitShiftAmount = _channelNumber * BDC_MOTOR_BITS_PER_CHANNEL;

    Xra1201::value &= ((uint16_t)~0x3F) << bitShiftAmount;
    Xra1201::value |= unsignedMotorTorque << bitShiftAmount;
    Xra1201::value |= effectiveMotorTorque < 0 ? ((uint16_t)0x20) << bitShiftAmount : 0;
}

void BdcMotor::setMotorTorque(float desiredMotorTorque)
{
    _motorTorque = desiredMotorTorque;
    if(desiredMotorTorque > MAX_BDC_MOTOR_TORQUE)
    {
        _motorTorque = MAX_BDC_MOTOR_TORQUE;
    }
    else if(desiredMotorTorque < MIN_BDC_MOTOR_TORQUE)
    {
        _motorTorque = MIN_BDC_MOTOR_TORQUE;
    }
}