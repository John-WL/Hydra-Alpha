// Author: John-William Lebel, 2021-04-13, creation

#include "Pca9685.h"

void Pca9685::init()
{
    static unsigned char data[2];
    
    // setup the output frequency prescaler
    data[0] = 0xFE;                 // prescaler register
    data[1] = PCA9685_PRE_SCALER;   // prescaler value
    _i2cDevice.transmit(data, sizeof(data));
}

void Pca9685::update(long registerValue, unsigned char channelNumber)
{
    static unsigned char data[2];
    unsigned char registerAddress = 0;
    unsigned char choppedRegisterValue = 0;

    for(unsigned char i = 0; i < PCA9685_AMOUNT_OF_BYTES_PER_CHANNEL; i++)
    {
        registerAddress = channelNumber * PCA9685_AMOUNT_OF_BYTES_PER_CHANNEL
            + PCA9685_LED_CONTROL_REGISTER_OFFSET;
        choppedRegisterValue = (unsigned char)(registerValue >> (i * 8));

        data[0] = registerAddress;
        data[1] = choppedRegisterValue;
        _i2cDevice.transmit(data, 2);
    }
}

I2cDevice Pca9685::_i2cDevice{I2C_ADDRESS_OF_ON_BOARD_PCA9685_SERVO_MOTOR_DRIVER};