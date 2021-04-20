// Author: John-William Lebel, 2021-04-13, creation

#ifndef PCA9685_H
#define PCA9685_H

#define I2C_ADDRESS_OF_ON_BOARD_PCA9685_SERVO_MOTOR_DRIVER 0x80
#define PCA9685_OUTPUT_FREQUENCY_HZ 50

#define PCA9685_CLOCK_FREQUENCY_HZ 25000000
#define PCA9685_PRE_SCALER (unsigned char) (PCA9685_CLOCK_FREQUENCY_HZ / (4096 * PCA9685_OUTPUT_FREQUENCY_HZ))

#define PCA9685_AMOUNT_OF_BYTES_PER_CHANNEL 4
#define PCA9685_LED_CONTROL_REGISTER_OFFSET 0x06

#include "../general_device/I2cDevice.h"

class Pca9685
{
    public:
        static void init();
        static void update(long registerValue, unsigned char channelNumber);

    private:
        static I2cDevice _i2cDevice;
};

#endif