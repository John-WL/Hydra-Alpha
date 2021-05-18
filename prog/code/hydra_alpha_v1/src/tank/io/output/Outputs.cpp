// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Arduino.h"

#include "Outputs.h"

#include "Vector.h"

#include "../../../shared/utils/sequence/Sequence.h"
#include "../../../shared/utils/math/vector/Vector3.h"
#include "../../../shared/utils/data_structure/CircularBuffer.h"
#include "../../utils/controllers/pid_controller/PidController.h"

#include "bdc_motor/BdcMotor.h"
#include "servo_motor/ServoMotor.h"
#include "debug_leds/DebugLeds.h"
#include "debug_leds/LedSequence.h"

#include "../../peripheral/i2c/xra1201/Xra1201.h"
#include "../../peripheral/i2c/bno055/Bno055.h"

#include "../input/sonar/SonarScanner.h"

void Outputs::init()
{
    Xra1201::init();
    LedSequence::init();
    LedSequence::setDisplayItem(LedSequencePreset::RETRO_LOADING);
    ServoMotor::initI2cCommunication();
}

void Outputs::update()
{
    _outputSequencer.update();
}

float Outputs::leftBdcPwmValues[] = {-0.98, -0.9, -0.82, -0.76, 0, 0.78, 0.82, 0.9, 1};
float Outputs::rightBdcPwmValues[] = {-1, -0.9, -0.85, -0.78, 0, 0.78, 0.85, 0.93, 1};

// bdc definitions
BdcMotor Outputs::bdcMotorLeft{1, 27, leftBdcPwmValues};
BdcMotor Outputs::bdcMotorRight{0, 14, rightBdcPwmValues};

// servo definitions
ServoMotor Outputs::servoMotorSonarZ{0, 4096 * 0.028, 4096 * 0.132};
ServoMotor Outputs::servoMotorCameraZ{1, 4096 * 0.026, 4096 * 0.122};
ServoMotor Outputs::servoMotorCameraY{2, 4096 * 0.035, 4096 * 0.09};

CircularBuffer<uint8_t> Outputs::_circularBuffer{10};
uint8_t Outputs::indexCircularBuffer{0};

// function sequence to update
std::vector<void (*)(void)> Outputs::_updateFunctions =
{
    []()
    {
        LedSequence::update();
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