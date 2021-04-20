// Author: John-William Lebel, 2021-04-11, creation

#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include "Vector.h"

class I2cDevice
{
    public:
        I2cDevice(unsigned char i2cDeviceAddress);

        void transmit(std::vector<unsigned char> data);
        std::vector<unsigned char> receive(unsigned char dataLengthRequest);

    private:
        unsigned char _i2cDeviceAddress;
        
};

#endif