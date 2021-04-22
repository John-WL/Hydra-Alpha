// Author: John-William Lebel, 2021-04-19, creation

#include "SlowSlaveI2c.h"

#include "Arduino.h"

#include "QueueArray.h"

#include "../../../../../projectConfig.h"  // for easy on/off debugging

void SlowSlaveI2c::init(uint8_t sdaPin, uint8_t sclPin, uint8_t chipAddress)
{
    _chipAddress = chipAddress & 0xFE;
    _receivedAddressSelect = ~_chipAddress;
    _sdaPin = sdaPin;
    _sclPin = sclPin;

    pinMode(_sdaPin, INPUT);
    pinMode(_sclPin, INPUT);
    digitalWrite(_sdaPin, LOW);
    _sdaCurrentState = digitalRead(_sdaPin);
    _sclCurrentState = digitalRead(_sclPin);

    _onSclFetch = _idleState;
    _onSclSync = _idleState;
}

void SlowSlaveI2c::update()
{
    // get the new state transitions
    _sdaPreviousState = _sdaCurrentState;
    _sclPreviousState = _sclCurrentState;
    _sdaCurrentState = _sdaRead();
    _sclCurrentState = _sclRead();

    // start/stop bit
    if(_sdaPreviousState != _sdaCurrentState)
    {
        _onSdaChange();
    }

    // data fetch/sync
    if(_sclPreviousState != _sclCurrentState)
    {
        _sclCurrentState ? 
            _onSclSync() :
            _onSclFetch();
    }
}

// start/stop bit handling
void SlowSlaveI2c::_onSdaChange()
{
    if(_gotStartBit())
    {
        _onSclFetch = _fetchAddressState;
        _onSclSync = _readAddressState;
        _readByte = 0;
        _bitCount = 0;
        _receivingData = true;
    }
    else if(_gotStopBit())
    {
        _onSclFetch = _idleState;
        _onSclSync = _idleState;
        _readByte = 0;
        _bitCount = 0;
        if(_receivingData && (_chipAddress == (_receivedAddressSelect & 0xFE)))
        {
            onReceive(_readData);
        }
        _receivedAddressSelect = ~_chipAddress;
        _receivingData = true;
        while(_writeData.count())
        {
            _writeData.pop();
        }
    }
}

void SlowSlaveI2c::_idleState()
{
    // Do nothing.
    // We are waiting for a start bit.
}

void SlowSlaveI2c::_fetchAddressState()
{
    // if we got the whole byte
    if(_bitCount == 8)
    {
        // that's our received address
        _receivedAddressSelect = _readByte;
        // if that's our chip address
        if(_receivedAddressSelect ^ _chipAddress <= 0x01)
        {
            _startAcknowledge();
        }
    }
    else if(_bitCount == 9)
    {
        _stopAcknowledge();

        // reset the data byte and bit count
        _readByte = 0;
        _bitCount = 0;
        // got a read bit?
        if((_chipAddress ^ _receivedAddressSelect) == 0)
        {
            _onSclFetch = _fetchReadDataState;
            _onSclSync = _readDataState;
        }
        // got a write bit?
        else if((_chipAddress ^ _receivedAddressSelect) == 1)
        {
            // reversed on purpose!
            _onSclFetch = _writeDataState;
            _onSclSync = _fetchWriteDataState;
            _receivingData = false;
            onRequest(_writeData);
            if(_writeData.count())
            {
                _writeByte = _writeData.pop();
            }
            // called because we are late in the "fetch-write" cycle,
            // and because we are in the "write" cycle right now...
            //_onSclSync();
            _onSclFetch();
        }
        // not the right chip address?
        else
        {
            _onSclFetch = _idleState;
            _onSclSync = _idleState;
        }
    }
}

void SlowSlaveI2c::_readAddressState()
{
    // update the "_readByte" variable
    if(_sdaCurrentState)
    {
        _readByte |= 0x80 >> _bitCount;
    }

    // got a bit, so index++
    _bitCount++;
}

void SlowSlaveI2c::_fetchReadDataState()
{
    if(_bitCount == 8)
    {
        _readData.push(_readByte);
        _startAcknowledge();
    }
    else if(_bitCount == 9)
    {
        _stopAcknowledge();
        _readByte = 0;
        _bitCount = 0;
    }
}

void SlowSlaveI2c::_readDataState()
{
    // update the "_readByte" variable
    if(_sdaCurrentState)
    {
        _readByte |= 0x80 >> _bitCount;
    }

    // got a bit, so index++
    _bitCount++;
}

void SlowSlaveI2c::_fetchWriteDataState()
{
    if(_bitCount == 9)
    {
        if(!_writeData.count())
        {
            _onSclFetch = _idleState;
            _onSclSync = _idleState;
            _sdaHigh();
            return;
        }
        _bitCount = 0;
        _writeByte = _writeData.pop();
    }
}

void SlowSlaveI2c::_writeDataState()
{
    if(_bitCount > 7)
    {
        if(_bitCount == 8)
        {
            _startAcknowledge();
        }
        else if(_bitCount == 9)
        {
            _sdaHigh();
        }
        // we have nothing to do here (all bits written), 
        // but we still need to notify that we got an 
        // additionnal "write state" execution
        _bitCount++;
        return;
    }

    // INPUT if 1
    // OUTPUT if 0
    (_writeByte & (0x80 >> _bitCount)) ?
        _sdaHigh() :
        _sdaLow();

    // we have written a bit, so index++
    _bitCount++;
}

bool SlowSlaveI2c::_gotStartBit()
{
    return !_sdaCurrentState && _sclCurrentState;
}

bool SlowSlaveI2c::_gotStopBit()
{
    return _sdaCurrentState && _sclCurrentState;
}

void SlowSlaveI2c::_startAcknowledge()
{
    if(_sendsAcknowledges)
    {
        _sdaLow();
    }
}

void SlowSlaveI2c::_stopAcknowledge()
{
    if(_sendsAcknowledges)
    {
        _sdaHigh();
    }
}

void SlowSlaveI2c::_sdaHigh()
{
    pinMode(_sdaPin, INPUT);
}

void SlowSlaveI2c::_sdaLow()
{
    pinMode(_sdaPin, OUTPUT);
}

bool SlowSlaveI2c::_sdaRead()
{
    return digitalRead(_sdaPin);
}

bool SlowSlaveI2c::_sclRead()
{
    return digitalRead(_sclPin);
}

void (*SlowSlaveI2c::_onSclSync)(void) = _idleState;
void (*SlowSlaveI2c::_onSclFetch)(void) = _idleState;

uint8_t SlowSlaveI2c::_chipAddress{0};
uint8_t SlowSlaveI2c::_sdaPin{0};
uint8_t SlowSlaveI2c::_sclPin{0};
bool SlowSlaveI2c::_sdaCurrentState{true};
bool SlowSlaveI2c::_sclCurrentState{true};
bool SlowSlaveI2c::_sdaPreviousState{true};
bool SlowSlaveI2c::_sclPreviousState{true};

uint8_t SlowSlaveI2c::_receivedAddressSelect{0};
bool SlowSlaveI2c::_receivingData{true};

bool SlowSlaveI2c::_sendsAcknowledges{false};

uint8_t SlowSlaveI2c::_bitCount{0};
uint8_t SlowSlaveI2c::_readByte{0};
uint8_t SlowSlaveI2c::_writeByte{0};
QueueArray<uint8_t> SlowSlaveI2c::_readData{};
QueueArray<uint8_t> SlowSlaveI2c::_writeData{};