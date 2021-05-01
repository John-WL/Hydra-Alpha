#include "LedSequence.h"

#include "Arduino.h"

#include "Vector.h"

#include "DebugLeds.h"

void LedSequence::init()
{
    _updateTimer.start();
}

void LedSequence::addDisplayItem(uint8_t displayItem)
{
    _sequence.push_back(displayItem);
}

void LedSequence::update()
{
    _updateTimer.update();
    DebugLeds::update();
}

void LedSequence::_updateTimeout()
{
    DebugLeds::displayValue = _sequence[_sequenceIndex];
    _sequenceIndex++;
    if(_sequenceIndex >= _sequence.size())
    {
        _sequenceIndex = 0;
    }
}

std::vector<uint8_t> LedSequence::_sequence{};
uint8_t LedSequence::_sequenceIndex{0};
TimerMicros LedSequence::_updateTimer
{
    TIMER_TIME_DELAY,
    _updateTimeout
};