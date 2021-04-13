// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Arduino.h"

#include "Outputs.h"

#include "Vector.h"

#include "../../utils/sequence/Sequence.h"

#include "../bdc_motor/BdcMotor.h"
#include "../servo_motor/ServoMotor.h"

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
BdcMotor Outputs::bdcMotorLeft{0};
BdcMotor Outputs::bdcMotorRight{1};

// servo definitions
ServoMotor Outputs::servoMotorSonarZ{0};
ServoMotor Outputs::servoMotorCameraZ{1};
ServoMotor Outputs::servoMotorCameraY{2};

// function sequence to update
std::vector<void (*)(void)> Outputs::_updateFunctions = {
    []()
    {
        bdcMotorLeft.update();
        bdcMotorRight.update();
    },
    []()
    {
        servoMotorSonarZ.update();
        servoMotorCameraZ.update();
        servoMotorCameraY.update();
    }
};

Sequence Outputs::_outputSequencer{_updateFunctions};