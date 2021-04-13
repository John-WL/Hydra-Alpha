// Author: John-William Lebel, 2021-04-11, creation

#include "BdcMotor.h"

#include "Arduino.h"

#include "../../peripheral/i2c/xra1201/Xra1201.h"

BdcMotor::BdcMotor(unsigned char channelNumber) : 
    _channelNumber{channelNumber},
    _motorTorque{0}
{}

void BdcMotor::update()
{
    unsigned char unsignedMotorTorque = abs(_motorTorque);
    unsigned int bitShiftAmount = _channelNumber * BDC_MOTOR_BITS_PER_CHANNEL;

    Xra1201::value &= ~0x3F << bitShiftAmount;
    Xra1201::value |= unsignedMotorTorque << bitShiftAmount;
    Xra1201::value |= _motorTorque < 0 ? 0x20 << bitShiftAmount : 0;
    
    Xra1201::update();
}

void BdcMotor::setMotorTorque(signed char desiredMotorTorque)
{
    _motorTorque = desiredMotorTorque;
    if(desiredMotorTorque > MAX_BDC_MOTOR_TORQUE)
    {
        _motorTorque = MAX_BDC_MOTOR_TORQUE;
    }
    else if(desiredMotorTorque < -MAX_BDC_MOTOR_TORQUE)
    {
        _motorTorque = -MAX_BDC_MOTOR_TORQUE;
    }
}