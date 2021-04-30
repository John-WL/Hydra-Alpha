// Author: John-William Lebel, 2021-04-11, creation

#ifndef XRA1201_H
#define XRA1201_H

#define I2C_ADDRESS_OF_ON_BOARD_XRA1201_BDC_DRIVER 0x40

#include "../general_device/I2cDevice.h"

#include "Arduino.h"

class Xra1201
{
    public:
        static void init();
        static void update();

        static uint16_t value;

    private:
        static I2cDevice _i2cDevice;
        static uint16_t _previousValue;
};

#endif