// Author: John-William Lebel, 2021-04-11, creation

#include "BdcMotor.h"

//#include "../../peripheral/i2c/xra1201/Xra1201.h"

// initialization done once every time we create a new object of this type
BdcMotor::BdcMotor(void (*hardwareAccessFunction)(signed char)) : 
    _hardwareAccessFunction{hardwareAccessFunction}, 
    _motorTorque{0}
{}

void BdcMotor::update()
{
    this->_hardwareAccessFunction(this->_motorTorque);
}

void BdcMotor::setMotorTorque(signed char newTorque)
{
    if(newTorque > MAX_BDC_MOTOR_TORQUE)
    {
        newTorque = MAX_BDC_MOTOR_TORQUE;
    }
    else if(newTorque < -MAX_BDC_MOTOR_TORQUE)
    {
        newTorque = -MAX_BDC_MOTOR_TORQUE;
    }
    this->_motorTorque = newTorque;
}

void BdcMotor::generalHardwareAccess(signed char motorTorque, unsigned char bitOffset)
{
    /*bool isTorqueNegative = false;
    if(motorTorque < 0)
    {
        isTorqueNegative = true;
        motorTorque = -motorTorque;
    }
    Xra1201::value ^= 0x3F << bitOffset;
    Xra1201::value |= motorTorque << bitOffset;
    if(isTorqueNegative)
    {
        Xra1201::value |= 0x20 << bitOffset;
    }
    Xra1201::update();*/
}