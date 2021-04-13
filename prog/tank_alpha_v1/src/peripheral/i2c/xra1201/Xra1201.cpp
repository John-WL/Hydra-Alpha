// Author: John-William Lebel, 2021-04-11, creation

#include "Xra1201.h"

void Xra1201::init()
{
    static unsigned char data[2];

    // Set the output registers value to 0 before 
    // changing the gpios to actual outputs.
    value = 0;
    update();
    
    data[0] = 0x06; // gpio config P0-P7
    data[1] = 0;    // the whole port is set as output
    _i2cDevice.transmit(data, sizeof(data));

    data[0] = 0x07; // gpio config P8-P15
    data[1] = 0;    // the whole port is set as output
    _i2cDevice.transmit(data, sizeof(data));
}

void Xra1201::update()
{
    static unsigned char data[2];

    // don't communicate for no reason
    if(value == _previousValue) return;

    // set P0-P7
    data[0] = 0x02; // gpio output control register
    data[1] = (unsigned char)value;
    _i2cDevice.transmit(data, 2);

    // set P8-P15
    data[0] = 0x03; // gpio output control register
    data[1] = (unsigned char)(value >> 8);
    _i2cDevice.transmit(data, 2);

    // Update the previous state so we can know if "value" changed
    // next time this function is called.
    _previousValue = value;
}

unsigned int Xra1201::value = 0;
unsigned int Xra1201::_previousValue = 0xFFF;

I2cDevice Xra1201::_i2cDevice{I2C_ADDRESS_OF_ON_BOARD_XRA1201_BDC_DRIVER};