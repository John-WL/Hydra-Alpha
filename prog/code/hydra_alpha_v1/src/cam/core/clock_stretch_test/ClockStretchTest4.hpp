// Author: John-William Lebel, 2021-04-20, creation

// Simple class to simulate and test clock stretching 
// in a closed environement before implementing it in
// the real word.

// This test tries to implement the clock-stretching mechanism 
// in a non-blocking fashion for the slave. 
// Other than that, it's the same thing as the ClockStretchTest3#3 class.



#ifndef CLOCK_STRETCH_TEST_4_H
#define CLOCK_STRETCH_TEST_4_H

#include "Arduino.h"

class ClockStretchTest4
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
        if(!digitalRead(_sclSlavePin) && !_sclLocked)
        {
            pinMode(_sclSlavePin, OUTPUT);
            _sclLocked = true;
            Serial.println("slave STRETCH");
            _time = millis() + 1000;
        }

        // this is for simulating the slave process that takes WAY too long
        if(millis() >= _time)
        {
            _sclReleaseRequest = true;
            _time = 0x7FFFFFFF;
        }
        
        if(_sclReleaseRequest)
        {
            _sclReleaseRequest = false;
            _sclLocked = false;
            pinMode(_sclSlavePin, INPUT);
            Serial.println("\nslave RELEASE");
            // release the clock line
        }
    }

private:
    static uint8_t _sclMasterPin;
    static uint8_t _sclSlavePin;
    static uint8_t _sclLocked;
    static uint8_t _sclReleaseRequest;
    static uint32_t _time;
    
};

uint8_t ClockStretchTest4::_sclMasterPin = 0;
uint8_t ClockStretchTest4::_sclSlavePin = 0;
uint8_t ClockStretchTest4::_sclLocked = false;
uint8_t ClockStretchTest4::_sclReleaseRequest = false;
uint32_t ClockStretchTest4::_time = 0x7FFFFFFF;




#endif