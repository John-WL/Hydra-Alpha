// Author: John-William Lebel, 2021-04-11, creation

// class used to control the bdc motors

#ifndef DEBUG_LED_H
#define DEBUG_LED_H

#define DEBUG_LED_LEFT_SHIFT_AMOUNT 12

class DebugLeds
{
    public:
        static void init();
        static void update();
        static unsigned char displayValue;

    private:
};

#endif