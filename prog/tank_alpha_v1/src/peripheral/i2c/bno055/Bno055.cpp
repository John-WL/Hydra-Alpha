// Author: John-William Lebel, 2021-04-12, creation

#include "Bno055.h"

Bno055::Bno055()
{
    _data = {};
    _bno055 = Adafruit_BNO055(55, 0x29);

    _bno055.begin();
    _bno055.setExtCrystalUse(true);

    _acceleration = &Vector3{};
    _orientation = &Orientation3{};
    _angularVelocity = &Vector3{};
}

void Bno055::update()
{
    _bno055.getEvent(&_data);
}

Vector3* Bno055::acceleration()
{
    return _acceleration;
}

Orientation3* Bno055::orientation()
{
    return _orientation;
}

Vector3* Bno055::angularVelocity()
{
    return _angularVelocity;
}