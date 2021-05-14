#include "LedSequence.h"

#include "Arduino.h"

#include "Vector.h"

#include "DebugLeds.h"

void LedSequence::init()
{
    DebugLeds::init();
    _updateTimer.start();
}

void LedSequence::addDisplayItem(uint8_t displayItem)
{
    _sequence.push_back(displayItem);
}

void LedSequence::setDisplayItem(LedSequencePreset::Enum presetEnum)
{
    switch(presetEnum)
    {
        case LedSequencePreset::RETRO_LOADING:
            _sequence.clear();
            LedSequence::addDisplayItem(0b1000);
            LedSequence::addDisplayItem(0b0100);
            LedSequence::addDisplayItem(0b0010);
            LedSequence::addDisplayItem(0b0001);
            LedSequence::addDisplayItem(0b1001);
            LedSequence::addDisplayItem(0b0101);
            LedSequence::addDisplayItem(0b0011);
            LedSequence::addDisplayItem(0b1011);
            LedSequence::addDisplayItem(0b0111);
            LedSequence::addDisplayItem(0b1111);
            LedSequence::addDisplayItem(0b1110);
            LedSequence::addDisplayItem(0b1101);
            LedSequence::addDisplayItem(0b1100);
            LedSequence::addDisplayItem(0b1010);
            LedSequence::addDisplayItem(0b1001);
            LedSequence::addDisplayItem(0b1000);
            LedSequence::addDisplayItem(0b0100);
            LedSequence::addDisplayItem(0b0010);
            LedSequence::addDisplayItem(0b0001);
            LedSequence::addDisplayItem(0b0010);
            LedSequence::addDisplayItem(0b0100);
            LedSequence::addDisplayItem(0b1000);
            LedSequence::addDisplayItem(0b0100);
            LedSequence::addDisplayItem(0b0010);
            LedSequence::addDisplayItem(0b0001);
            break;
    }
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