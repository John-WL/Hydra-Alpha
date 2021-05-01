// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Arduino.h"

#include "Outputs.h"

#include "Vector.h"

#include "../../../shared/utils/sequence/Sequence.h"

#include "bdc_motor/BdcMotor.h"
#include "servo_motor/ServoMotor.h"
#include "debug_leds/DebugLeds.h"
#include "debug_leds/LedSequence.h"

#include "../../peripheral/i2c/xra1201/Xra1201.h"

void Outputs::init()
{
    Xra1201::init();
    DebugLeds::init();
    LedSequence::addDisplayItem(0b1111);
    LedSequence::addDisplayItem(0b0000);
    LedSequence::addDisplayItem(0b0001);
    LedSequence::addDisplayItem(0b0010);
    LedSequence::addDisplayItem(0b0100);
    LedSequence::addDisplayItem(0b1000);
    ServoMotor::initI2cCommunication();
}

void Outputs::update()
{
    // updated every frame
    bdcMotorLeft.update();
    bdcMotorRight.update();

    // I2C and everything that needs to be handled turn by turn
    _outputSequencer.update();
}

// bdc definitions
BdcMotor Outputs::bdcMotorLeft{0, 14};
BdcMotor Outputs::bdcMotorRight{1, 27};

// servo definitions
ServoMotor Outputs::servoMotorSonarZ{0, 4096 * 0.028, 4096 * 0.132};
ServoMotor Outputs::servoMotorCameraZ{1, 4096 * 0.026, 4096 * 0.122};
ServoMotor Outputs::servoMotorCameraY{2, 4096 * 0.035, 4096 * 0.09};

// function sequence to update
std::vector<void (*)(void)> Outputs::_updateFunctions =
{
    []()
    {
        LedSequence::update();
        Xra1201::update();

        servoMotorSonarZ.setMotorAngle(0);
        servoMotorCameraZ.setMotorAngle(0);
        servoMotorCameraY.setMotorAngle(0);

        servoMotorSonarZ.update();
        servoMotorCameraZ.update();
        servoMotorCameraY.update();
    }
};

Sequence Outputs::_outputSequencer{_updateFunctions};