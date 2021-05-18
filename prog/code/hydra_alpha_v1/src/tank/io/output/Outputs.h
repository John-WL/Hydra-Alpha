// Author: John-William Lebel, 2021-04-08, creation

// simple section of code where we update the outputs on the board

#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "Vector.h"

#include "../../../shared/utils/sequence/Sequence.h"
#include "../../../shared/utils/data_structure/CircularBuffer.h"

#include "bdc_motor/BdcMotor.h"
#include "servo_motor/ServoMotor.h"
#include "debug_leds/DebugLeds.h"

class Outputs
{
    public:
        static void init();
        static void update();

        static float leftBdcPwmValues[];
        static float rightBdcPwmValues[];

        static BdcMotor bdcMotorLeft;
        static BdcMotor bdcMotorRight;

        static ServoMotor servoMotorSonarZ;
        static ServoMotor servoMotorCameraZ;
        static ServoMotor servoMotorCameraY;
        
    private:
        static std::vector<void (*)(void)> _updateFunctions;

        static Sequence _outputSequencer;
        static CircularBuffer<uint8_t> _circularBuffer;
        static uint8_t indexCircularBuffer;
};

#endif