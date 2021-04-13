// Author: John-William Lebel, 2021-04-12, creation

// communication with a Bno055 device by I2C at address 0x29

#ifndef BNO055_H
#define BNO055_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Bno055
{
    public:
        static void init();
        static void update();

        static sensors_event_t data;
    private:
        static Adafruit_BNO055 _bno055;
};

#endif