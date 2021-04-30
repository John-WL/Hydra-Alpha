// Author: John-William Lebel, 2021-04-13, creation

// class used to control the servo motors

#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "Arduino.h" // PI constant defined in here

#include "../../../utils/controllers/exponential_controller/ExponentialController.h"

#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"

// adding 0.5 to round values instead of flooring them
#define SERVO_MOTOR_MIN_VALUE_FOR_PCA9685 (4096 * 0.05 + 0.5)
#define SERVO_MOTOR_MAX_VALUE_FOR_PCA9685 (4096 * 0.2 + 0.5)
#define SERVO_MOTOR_ANGLE_VALUE_RANGE_SIZE (SERVO_MOTOR_MAX_VALUE_FOR_PCA9685 - SERVO_MOTOR_MIN_VALUE_FOR_PCA9685)

#define ONE_OVER_PI (1 / PI)

class ServoMotor
{
    public:
        static void initI2cCommunication();

        ServoMotor(unsigned char channelNumber);
        ServoMotor(unsigned char channelNumber,
            unsigned int minServoValueForPca9685,
            unsigned int maxServoValueForPca9685);
        void update();
        float getMotorAngle();
        void setMotorAngle(float motorAngle);

    private:
        static Adafruit_PWMServoDriver _servoDriver;

        unsigned char _channelNumber;   // 0 to 15
        unsigned int _minServoValueForPca9685;
        unsigned int _servoValueRangeForPca9685;
        float _motorAngle;              // radians
        unsigned int _previousRegisterValues;
        ExponentialController _smoothController;
};

#endif