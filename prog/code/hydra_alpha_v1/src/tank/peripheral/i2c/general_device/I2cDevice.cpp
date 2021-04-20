// Author: John-William Lebel, 2021-04-11, creation

#include "I2cDevice.h"

#include "../I2cProtocol.h"

#include "Vector.h"

I2cDevice::I2cDevice(unsigned char i2cDeviceAddress) :
    _i2cDeviceAddress{i2cDeviceAddress}
{}

void I2cDevice::transmit(std::vector<unsigned char> data)
{
    I2cProtocol::transmit(_i2cDeviceAddress, data);
}

std::vector<unsigned char> I2cDevice::receive(unsigned char dataLengthRequest)
{
    return I2cProtocol::receive(_i2cDeviceAddress, dataLengthRequest);
}