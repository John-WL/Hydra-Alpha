
#ifndef LED_SEQUENCE
#define LED_SEQUENCE

#include "Arduino.h"

#include "Vector.h"

#include "../../../../shared/utils/timer/TimerMicros.h"

#define TIMER_TIME_DELAY 500000

class LedSequence
{
public:
    static void init();
    static void addDisplayItem(uint8_t displayItem);
    static void update();

private:
    static void _updateTimeout();

    static std::vector<uint8_t> _sequence;
    static uint8_t _sequenceIndex;
    static TimerMicros _updateTimer;
};

#endif