// Author: John-William Lebel, 2021-04-11, creation

#include "I2cDevice.h"

#include "../I2cProtocol.h"

I2cDevice::I2cDevice(unsigned char i2cDeviceAddress) : _i2cDeviceAddress{i2cDeviceAddress}
{}

void I2cDevice::transmit(unsigned char* data, unsigned char dataLength)
{
    I2cProtocol::transmit(_i2cDeviceAddress, data, dataLength);
}

unsigned char* I2cDevice::receive(unsigned char dataLength)
{
    return I2cProtocol::receive(_i2cDeviceAddress, dataLength);
}