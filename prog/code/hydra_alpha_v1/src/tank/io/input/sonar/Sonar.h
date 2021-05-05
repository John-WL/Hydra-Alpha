// Author: John-William Lebel, 2021-04-13, creation

// class to handle the on-board sonar

// How it works:
// First, you need to change the trig and echo pins so it works on your desing. 
// To initialize the class, call the "init([](long distance){})" constructor, and put 
// code that handles reception of data in the labda.
// To use the sonar, just call the "requestUpdate()" function as often as
// you need to. This class handles request overhead, so you don't need to 
// worry about calling the request function too much. 

// The reason we are using a lambda instead of a simple variable is
// because the reception of data can take a while to complete
// (up to about 23ms at worst, which is pretty bad for any time
// sensitive app, if you ask me). Therefore, we kind of want to
// continue the execution of the code, even if we didn't receive the
// distance data just yet. In order to do so, we need to have in place
// an interrupt function that gets called to handle the data when it's
// ready, instead of waiting for it by wasting cpu cycles.

#ifndef SONAR_H
#define SONAR_H

#include "Arduino.h"

#include "SonarSample.h"

#define SONAR_TRIG_PIN 25
#define SONAR_ECHO_PIN 26

#define SONAR_RECEPTION_TIMEOUT_MICROSECONDS 23529  // equivalent to 4 meters, so about max range for this sensor
#define SPEED_OF_SOUND_IN_AIR 343
#define SONAR_MICROSECONDS_TO_MM_FACTOR (SPEED_OF_SOUND_IN_AIR * 0.0005)
#define SONAR_DISTANCE_OFFSET 59

class Sonar
{
    public:
        static void init(void (*callback)(SonarSample));
        static void requestUpdate();
        static int32_t measuredDistance;

    private:
        static void IRAM_ATTR onEchoReceive();
        static void handlePotentialTimeout();
        static void (*_callback)(SonarSample); // called when we have a valid sonar response

        static bool _waitingForReception;
        static uint32_t _timeOfRequest;
        static uint32_t _duration;
};

#endif