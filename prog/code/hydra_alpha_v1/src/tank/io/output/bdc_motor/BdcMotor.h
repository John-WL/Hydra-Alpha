// Author: John-William Lebel, 2021-04-11, creation

// class used to control the bdc motors

#ifndef BDC_MOTOR_H
#define BDC_MOTOR_H

#include "../../../utils/controllers/pulse_controller/Int8_tPulseController.h"

#define MAX_BDC_MOTOR_TORQUE 32
#define MIN_BDC_MOTOR_TORQUE -32

#define BDC_MOTOR_BITS_PER_CHANNEL 6

class BdcMotor
{
    public:
        BdcMotor(unsigned char channelNumber);
        void update();
        void setMotorTorque(float desiredTorque);

    private:
        unsigned char _channelNumber;
        float _motorTorque;
        Int8_tPulseController _pulseController;
};

#endif