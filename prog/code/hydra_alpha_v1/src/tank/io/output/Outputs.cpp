// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Arduino.h"

#include "Outputs.h"

#include "Vector.h"

#include "../../../shared/utils/sequence/Sequence.h"
#include "../../../shared/utils/math/vector/Vector3.h"
#include "../../utils/controllers/pid_controller/PidController.h"

#include "bdc_motor/BdcMotor.h"
#include "servo_motor/ServoMotor.h"
#include "debug_leds/DebugLeds.h"
#include "debug_leds/LedSequence.h"

#include "../../peripheral/i2c/xra1201/Xra1201.h"
#include "../../peripheral/i2c/bno055/Bno055.h"

void Outputs::init()
{
    Xra1201::init();
    LedSequence::init();
    LedSequence::addDisplayItem(0b0000);
    LedSequence::addDisplayItem(0b1000);
    LedSequence::addDisplayItem(0b0100);
    LedSequence::addDisplayItem(0b0010);
    LedSequence::addDisplayItem(0b0001);
    LedSequence::addDisplayItem(0b1001);
    LedSequence::addDisplayItem(0b0101);
    LedSequence::addDisplayItem(0b0011);
    LedSequence::addDisplayItem(0b1011);
    LedSequence::addDisplayItem(0b0111);
    LedSequence::addDisplayItem(0b1111);
    LedSequence::addDisplayItem(0b1110);
    LedSequence::addDisplayItem(0b1101);
    LedSequence::addDisplayItem(0b1100);
    LedSequence::addDisplayItem(0b1010);
    LedSequence::addDisplayItem(0b1001);
    LedSequence::addDisplayItem(0b1000);
    LedSequence::addDisplayItem(0b0100);
    LedSequence::addDisplayItem(0b0010);
    LedSequence::addDisplayItem(0b0001);
    LedSequence::addDisplayItem(0b0010);
    LedSequence::addDisplayItem(0b0100);
    LedSequence::addDisplayItem(0b1000);
    LedSequence::addDisplayItem(0b0100);
    LedSequence::addDisplayItem(0b0010);
    LedSequence::addDisplayItem(0b0001);
    ServoMotor::initI2cCommunication();
}

void Outputs::update()
{

    // I2C and everything that needs to be handled turn by turn
    _outputSequencer.update();
}

// bdc definitions
BdcMotor Outputs::bdcMotorLeft{1, 27};
BdcMotor Outputs::bdcMotorRight{0, 14};

// servo definitions
ServoMotor Outputs::servoMotorSonarZ{0, 4096 * 0.028, 4096 * 0.132};
ServoMotor Outputs::servoMotorCameraZ{1, 4096 * 0.026, 4096 * 0.122};
ServoMotor Outputs::servoMotorCameraY{2, 4096 * 0.035, 4096 * 0.09};

// function sequence to update
std::vector<void (*)(void)> Outputs::_updateFunctions =
{
    []()
    {
        //bdcMotorLeft.setMotorTorque(-Vector3{1, 0, 0}.findRotator(Bno055::orientation().front).z*3.2 + Bno055::angularVelocity().z*0.3);
        //bdcMotorRight.setMotorTorque(-Vector3{1, 0, 0}.findRotator(Bno055::orientation().front).z*3.2 + Bno055::angularVelocity().z*0.3);

        servoMotorSonarZ.setMotorAngle(Vector3{1, 0, 0}.findRotator(Bno055::orientation().front).z);
        servoMotorCameraZ.setMotorAngle(Vector3{1, 0, 0}.findRotator(Bno055::orientation().front).z);
        servoMotorCameraY.setMotorAngle(0);

        LedSequence::update();
    },
    []()
    {
        Xra1201::update();
    },
    []()
    {
        servoMotorSonarZ.update();
        servoMotorCameraZ.update();
        servoMotorCameraY.update();
    }
};

Sequence Outputs::_outputSequencer{_updateFunctions};