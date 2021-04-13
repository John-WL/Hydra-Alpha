// Author: John-William Lebel, 2021-04-13, creation

// class to handle the on-board sonar

#ifndef SONAR_H
#define SONAR_H

#include "Arduino.h"

#define SONAR_TRIG_PIN 25
#define SONAR_ECHO_PIN 26

#define SONAR_RECEPTION_TIMEOUT_MICROSECONDS 23529  // equivalent to 4 meters, so about max range for this sensor
#define SPEED_OF_SOUND_IN_AIR 343
#define SONAR_MICROSECONDS_TO_MM_FACTOR (SPEED_OF_SOUND_IN_AIR * 0.001 / 2)

class Sonar
{
    public:
        static void init(void (*callback)(long));
        static void requestUpdate();

    private:
        static void IRAM_ATTR onEchoReceive();
        static void handlePotentialTimeout();
        static void (*_callback)(long); // called when we got new sonar data

        static bool _waitingForReception;
        static long _timeOfRequest;
        static long _duration;
};

#endif