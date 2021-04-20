// Author: John-William Lebel, 2021-04-12, creation

// communication with a Bno055 device by I2C at address 0x29

#ifndef BNO055_H
#define BNO055_H

#include "../../../../shared/utils/math/vector/Vector3.h"
#include "../../../../shared/utils/math/vector/Orientation3.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Bno055
{
    public:
        static void init();
        static void update();

        static Vector3 acceleration();
        static Orientation3 orientation();
        static Vector3 angularVelocity();

    private:
        static sensors_event_t _data;
        static Adafruit_BNO055 _bno055;
        static Vector3 _acceleration;
        static Orientation3 _orientation;
        static Vector3 _angularVelocity;
        
};

#endif