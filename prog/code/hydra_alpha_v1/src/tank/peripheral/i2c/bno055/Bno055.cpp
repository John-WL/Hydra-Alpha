// Author: John-William Lebel, 2021-04-12, creation

#include "Bno055.h"

#include "../../../../shared/utils/math/vector/Orientation3.h"
#include "../../../../shared/utils/math/vector/Vector3.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

void Bno055::init()
{
    _bno055.begin();
    _bno055.setExtCrystalUse(true);
}

void Bno055::update()
{
    _bno055.getEvent(&_data);
    _orientation = Orientation3::eulerXyzToOrientation(Vector3{_data});
    _angularVelocity = Vector3{_bno055.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE)};
    _acceleration = Vector3{_bno055.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER)};
}

Vector3 Bno055::acceleration()
{
    return _acceleration;
}

Orientation3 Bno055::orientation()
{
    return _orientation;
}

Vector3 Bno055::angularVelocity()
{
    return _angularVelocity;
}

sensors_event_t Bno055::_data{};
Adafruit_BNO055 Bno055::_bno055{55, 0x28};
Vector3 Bno055::_acceleration{};
Orientation3 Bno055::_orientation{};
Vector3 Bno055::_angularVelocity{};