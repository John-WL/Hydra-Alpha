// Author: John-William Lebel, 2021-04-11, creation

#include "Xra1201.h"

#include "Vector.h"

void Xra1201::init()
{
    std::vector<unsigned char> data{};

    // Set the output registers value to 0 before 
    // changing the gpios to actual outputs.
    value = 0;
    update();
    
    data.push_back(0x06); // gpio config P0-P7
    data.push_back(0);    // the whole port is set as output
    _i2cDevice.transmit(data);

    data.clear();
    data.push_back(0x07); // gpio config P8-P15
    data.push_back(0);    // the whole port is set as output
    _i2cDevice.transmit(data);
}

void Xra1201::update()
{
    std::vector<unsigned char> data{};

    // don't communicate for no reason
    if(value == _previousValue) return;

    // set P0-P7
    data.push_back(0x02); // gpio output control register
    data.push_back((unsigned char) value);
    _i2cDevice.transmit(data);

    // set P8-P15
    data.clear();
    data.push_back(0x03); // gpio output control register
    data.push_back((unsigned char)(value >> 8));
    _i2cDevice.transmit(data);

    // Update the previous state so we can know if "value" changed
    // next time this function is called.
    _previousValue = value;
}

unsigned int Xra1201::value = 0;
unsigned int Xra1201::_previousValue = 0xFFF;

I2cDevice Xra1201::_i2cDevice{I2C_ADDRESS_OF_ON_BOARD_XRA1201_BDC_DRIVER};