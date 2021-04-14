// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "TimerMicros.h"

#include "../constants/Constants.h"

TimerMicros::TimerMicros(long durationMicroseconds, void (*recurrentCallback)(void)) : 
    _duration{durationMicroseconds},
    _recurrentCallback{recurrentCallback},
    _nextTime{LONG_MAX_VALUE}
{}

void TimerMicros::start()
{
    _nextTime = micros() + _duration;
}

void TimerMicros::update()
{
    if(this->elapsedAutoReload())
    {
        (*TimerMicros::_recurrentCallback)();
    }
}

bool TimerMicros::elapsedAutoReload()
{
    bool hasElapsed = this->elapsed();
    if(hasElapsed)
    {
        this->lapse();
    }
    return hasElapsed;
}

bool TimerMicros::elapsed()
{
    return _nextTime < micros();
}

void TimerMicros::lapse()
{
    _nextTime += _duration;
}
