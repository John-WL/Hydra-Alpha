// Author: John-William Lebel, 2021-04-12, creation

#include "Bno055.h"

void Bno055::init()
{
    _bno055.begin();
    _bno055.setExtCrystalUse(true);
}

void Bno055::update()
{
    _bno055.getEvent(&data);
}

Adafruit_BNO055 Bno055::_bno055 = Adafruit_BNO055(55, 0x29);