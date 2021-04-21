// Author: John-William Lebel, 2021-04-20, creation

// Simple class to simulate and test clock stretching 
// in a closed environement before implementing it in
// the real word.

// This test is an attempt at handling full-speed I2C clock stretching
// by utilizing interrupts. 

#ifndef CLOCK_STRETCH_TEST_2_H
#define CLOCK_STRETCH_TEST_2_H

#include "Arduino.h"

class ClockStretchTest2
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

        attachInterrupt(digitalPinToInterrupt(_sclSlavePin), _sclSlaveClockStrech, FALLING);
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
        if(!_sclSlaveState)
        {
            Serial.println("slave STRETCH");

            // clock stretching is handled with interrupts

            // this is for simulating the slave process that takes WAY too long
            delay(4000);

            Serial.println("\nslave RELEASE");
            // release the clock line
            pinMode(_sclSlavePin, INPUT);
            _sclSlaveState = 1;
        }
    }

private:
    static void _sclSlaveClockStrech()
    {
        pinMode(_sclSlavePin, INPUT);
        _sclSlaveState = 0;
    }

    static uint8_t _sclMasterPin;
    static uint8_t _sclSlavePin;
    static uint8_t _sclSlaveState;
    
};

uint8_t ClockStretchTest2::_sclMasterPin = 0;
uint8_t ClockStretchTest2::_sclSlavePin = 0;
uint8_t ClockStretchTest2::_sclSlaveState = 0;


#endif