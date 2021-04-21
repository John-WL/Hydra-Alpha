// Author: John-William Lebel, 2021-04-20, creation

// Simple class to simulate and test clock stretching 
// in a closed environement before implementing it in
// the real word.

// Note: all experiments were performed on the Esp-WROOM-32
// - Crystal frequency @40MHz

// Hypothesis:
// This test will show why simple methods using
// arduino's digitalRead() function calls don't work
// properly.

// Reality:
// The digitalRead() function call in the context of
// Esp32 programmed with arduino can done in about 0.2µS (or 5 MHz).
// In contrast, performing a pinMode() function call takes 2.6µS (or ~385 KHz).

// Conclusion:
// The experiment shows that we can use the digitalRead() function
// to perform clock stretching in the custom I2C protocol. 

// That being said, it might be more efficient to use digital interrupts
// instead of the arduino functions to detect falling edges and handle them. 



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
        // the esp32 used with arduino can call digitalRead() (and optionnaly put the 
        // result in a uint8_t variable) at 5MHz. 
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