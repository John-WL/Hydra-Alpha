// Author: John-William Lebel, 2021-04-20, creation

// Simple class to simulate and test clock stretching 
// in a closed environement before implementing it in
// the real word.

// This test tries to show why simple methods using
// arduino's digitalRead() function calls don't work
// properly.

#ifndef CLOCK_STRETCH_TEST_3_H
#define CLOCK_STRETCH_TEST_3_H

#include "Arduino.h"

class ClockStretchTest3
{
public:
    static void init(uint8_t sclMasrerPin, uint8_t sclSlavePin)
    {
        _sclMasterPin = sclMasrerPin;
        _sclSlavePin = sclSlavePin;
        pinMode(_sclMasterPin, INPUT);
        pinMode(_sclSlavePin, INPUT);
        digitalWrite(_sclMasterPin, LOW);
        digitalWrite(_sclSlavePin, LOW);
    }

    static void updateMaster()
    {
        Serial.println("\n\nmaster FETCH");

        // very quick high-low-high pulse
        pinMode(_sclMasterPin, OUTPUT);
        pinMode(_sclMasterPin, INPUT);

        Serial.println("master SYNC");
        while(!digitalRead(_sclMasterPin))
        {}
    }

    static void updateSlave()
    {
        if(!digitalRead(_sclSlavePin))
        {
            Serial.println("slave STRETCH");
            // for clock-stretch
            pinMode(_sclSlavePin, OUTPUT);

            // this is for simulating the slave process that takes WAY too long
            delay(1000);

            Serial.println("\nslave RELEASE");
            // release the clock line
            pinMode(_sclSlavePin, INPUT);
        }
    }

private:
    static uint8_t _sclMasterPin;
    static uint8_t _sclSlavePin;
    
};

uint8_t ClockStretchTest3::_sclMasterPin = 0;
uint8_t ClockStretchTest3::_sclSlavePin = 0;

#endif