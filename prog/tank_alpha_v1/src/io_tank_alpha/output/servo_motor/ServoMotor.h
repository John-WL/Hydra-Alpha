// Author: John-William Lebel, 2021-04-13, creation

// class used to control the servo motors

#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#define SERVO_MOTOR_MIN_VALUE_FOR_PCA9685 (4096 * 0.05 + 0.5)
#define SERVO_MOTOR_MAX_VALUE_FOR_PCA9685 (4096 * 0.2 + 0.5)
#define SERVO_MOTOR_ANGLE_VALUE_RANGE_SIZE SERVO_MOTOR_MAX_VALUE_FOR_PCA9685 - SERVO_MOTOR_MIN_VALUE_FOR_PCA9685

#define PI 3.14159265358979
#define ONE_OVER_PI 1 / PI

class ServoMotor
{
    public:
        ServoMotor(unsigned char channelNumber);
        void update();
        float getMotorAngle();
        void setMotorAngle(float motorAngle);

    private:
        float _motorAngle;              // radians
        float _previousMotorAngle;
        unsigned char _channelNumber;   // 0 to 15
};

#endif