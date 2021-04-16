// Author: John-William Lebel, 2021-04-13, creation

#include "Pca9685.h"

void Pca9685::init()
{
    std::vector<unsigned char> data{};
    
    // setup the output frequency prescaler
    data.push_back(0xFE);                 // prescaler register
    data.push_back(PCA9685_PRE_SCALER);   // prescaler value
    _i2cDevice.transmit(data);
}

void Pca9685::update(long valueToPutInRegisters, unsigned char channelNumber)
{
    std::vector<unsigned char> data{};
    unsigned char registerAddress = 0;
    unsigned char choppedValueToPutInRegister = 0;

    for(unsigned char i = 0; i < PCA9685_AMOUNT_OF_BYTES_PER_CHANNEL; i++)
    {
        registerAddress = channelNumber * PCA9685_AMOUNT_OF_BYTES_PER_CHANNEL
            + PCA9685_LED_CONTROL_REGISTER_OFFSET;
        choppedValueToPutInRegister = (unsigned char)(valueToPutInRegisters >> (i * 8));

        data.clear();
        data.push_back(registerAddress);
        data.push_back(choppedValueToPutInRegister);
        _i2cDevice.transmit(data);
    }
}

I2cDevice Pca9685::_i2cDevice{I2C_ADDRESS_OF_ON_BOARD_PCA9685_SERVO_MOTOR_DRIVER};