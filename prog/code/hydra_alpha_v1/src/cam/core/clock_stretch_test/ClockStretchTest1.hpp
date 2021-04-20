// Author: John-William Lebel, 2021-04-20, creation

// Simple class to simulate and test clock stretching 
// in a closed environement before implementing it in
// the real word.

// This test shows the basic implementation that wouldn't
// work in the real world because of the bad reaction timings.
// It's a proof of concept that shows how to handle clock-stretching
// in a very-slow speed environment. 

#ifndef CLOCK_STRETCH_TEST_1_H
#define CLOCK_STRETCH_TEST_1_H

#include "Arduino.h"

class ClockStretchTest1
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
        pinMode(_sclMasterPin, OUTPUT);

        // Normaly, this is removed when we handle the
        // falling edge on the slave device with an interrupt.
        // For now, we use this to make sure the slave
        // has enough time to read the low signal.
        delayMicroseconds(300);

        Serial.println("master SYNC");
        pinMode(_sclMasterPin, INPUT);
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
            delay(4000);

            Serial.println("\nslave RELEASE");
            // release the clock line
            pinMode(_sclSlavePin, INPUT);
        }
    }

private:
    static uint8_t _sclMasterPin;
    static uint8_t _sclSlavePin;
    
};

uint8_t ClockStretchTest1::_sclMasterPin = 0;
uint8_t ClockStretchTest1::_sclSlavePin = 0;

#endif