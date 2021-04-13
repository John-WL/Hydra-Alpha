// Author: John-William Lebel, 2021-04-12, creation

// communication with a Bno055 device by I2C at address 0x29

#ifndef BNO055_H
#define BNO055_H

#include "../../../io_tank_alpha/input/imu/Imu.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Bno055 : Imu
{
    public:
        Bno055();
        void update();

    private:
        sensors_event_t _data;
        Adafruit_BNO055 _bno055;
        Vector3* _acceleration;
        Orientation3* _orientation;
        Vector3* _angularVelocity;
        
};

#endif