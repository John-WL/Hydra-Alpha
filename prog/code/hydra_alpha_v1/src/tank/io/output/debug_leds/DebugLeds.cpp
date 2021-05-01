// Author: John-William Lebel, 2021-04-11, creation

#include "DebugLeds.h"

#include "Arduino.h"

#include "../../../peripheral/i2c/xra1201/Xra1201.h"

void DebugLeds::init()
{}

void DebugLeds::update()
{
    Xra1201::value &= ~(0x000F << DEBUG_LED_LEFT_SHIFT_AMOUNT);
    Xra1201::value |= displayValue << DEBUG_LED_LEFT_SHIFT_AMOUNT;
}

unsigned char DebugLeds::displayValue{0};