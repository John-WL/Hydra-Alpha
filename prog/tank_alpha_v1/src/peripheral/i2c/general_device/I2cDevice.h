// Author: John-William Lebel, 2021-04-11, creation

#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

class I2cDevice
{
    public:
        I2cDevice(unsigned char i2cDeviceAddress);

        void transmit(unsigned char* data, unsigned char dataLength);
        unsigned char* receive(unsigned char dataLength);
    private:
        unsigned char _i2cDeviceAddress;
};

#endif