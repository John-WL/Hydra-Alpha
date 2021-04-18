// Author: John-William Lebel, 2021-04-10, creation

// class giving access to the second core of the esp32

#ifndef ESP32_DUAL_CORE_H
#define ESP32_DUAL_CORE_H

#include "Arduino.h"

#define SECOND_CORE_USABLE_STACK_SIZE 10000

class Esp32DualCore
{
public:
    static void init();
    static void main();

private:
    static void _secondCoreRootTask(void* params);

};

#endif