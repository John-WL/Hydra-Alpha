// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Arduino.h"

#include "Outputs.h"

#include "Vector.h"

#include "../../utils/sequence/Sequence.h"

#include "../../peripheral/i2c/xra1201/Xra1201.h"

void Outputs::init()
{
    Xra1201::init();
}

void Outputs::update()
{
    _outputSequencer.update();
}

// bdc definitions
BdcMotor Outputs::bdcMotorLeft
{
    [](signed char motorTorque)
    {
        BdcMotor::generalHardwareAccess(motorTorque, 0);
    }
};

BdcMotor Outputs::bdcMotorRight
{
    [](signed char motorTorque)
    {
        BdcMotor::generalHardwareAccess(motorTorque, 6);
    }
};

// function sequence to update
std::vector<void (*)(void)> Outputs::_updateFunctions = {
    []()
    {
        Outputs::bdcMotorLeft.update();
        Outputs::bdcMotorRight.update();
    }
};

Sequence Outputs::_outputSequencer{_updateFunctions};