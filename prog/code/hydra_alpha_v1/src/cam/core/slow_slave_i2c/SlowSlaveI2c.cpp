// Author: John-William Lebel, 2021-04-19, creation

#include "SlowSlaveI2c.h"

#include "Arduino.h"

#include "QueueArray.h"

#include "../../../../projectConfig.h"  // for easy on/off debugging

void SlowSlaveI2c::init(uint8_t sdaPin, uint8_t sclPin, uint8_t chipAddress)
{
    serialDebug("slow I2C init");
    _chipAddress = chipAddress & 0xFE;
    _receivedAddressSelect = ~_chipAddress;
    _sdaPin = sdaPin;
    _sclPin = sclPin;

    pinMode(_sdaPin, INPUT);
    pinMode(_sclPin, INPUT);
    digitalWrite(_sdaPin, LOW);
    _sdaCurrentState = digitalRead(_sdaPin);
    _sclCurrentState = digitalRead(_sclPin);

    _onSclSync = _idleState;
}

void SlowSlaveI2c::update()
{
    // get the new state transitions
    _sdaPreviousState = _sdaCurrentState;
    _sclPreviousState = _sclCurrentState;
    _sdaCurrentState = _sdaRead();
    _sclCurrentState = _sclRead();

    if(_gotStartBit())
    {
        serialDebug("start");
        _onSclSync = _readAddressState;
        _bitCount = 0;
        _readByte = 0;
        _receivingData = true;
    }
    else if(_gotStopBit())
    {
        serialDebug("stop");
        _onSclSync = _idleState;
        _readByte = 0;
        _bitCount = 0;
        if(_receivingData
            && (_chipAddress == (_receivedAddressSelect & 0xFE)))
        {
            onReceive(_readData);
        }
        _receivingData = true;
        _receivedAddressSelect = ~_chipAddress;
        while(_writeData.count())
        {
            _writeData.pop();
        }
    }
    
    if(_sclFalling())
    {
        //serialDebug("scl fall");
        _lockLowSclLine();
        _stopAcknowledge();
        _onSclSync();
        _releaseSclLine();
    }
}

void SlowSlaveI2c::_idleState()
{
    // Do nothing.
    // We are waiting for a start bit.
}

void SlowSlaveI2c::_readAddressState()
{
    delayMicroseconds(I2C_SLAVE_DELAY_FOR_SDA_UPDATE);

    if(_bitCount < 8)
    {
        _readByte |= digitalRead(_sdaPin) ? 
            0x80 >> _bitCount :
            0;
    }
    else if((_readByte ^ _chipAddress) <= 1)
    {
        _receivedAddressSelect = _readByte;
        _startAcknowledge();    // ack if we are the chosen one
        if((_receivedAddressSelect ^ _chipAddress) == 0) // if we are in reading state
        {
            _onSclSync = _readDataState;
        }
        else if((_receivedAddressSelect ^ _chipAddress) == 1) // if we are in writing state
        {
            _onSclSync = _writeDataState;
            _receivingData = false;
            onRequest(_writeData);
        }
        _bitCount = 0;
        _readByte = 0;
    }

    _bitCount++;
}

void SlowSlaveI2c::_readDataState()
{
    delayMicroseconds(I2C_SLAVE_DELAY_FOR_SDA_UPDATE);

    if(_bitCount < 8)
    {
        _readByte |= digitalRead(_sdaPin) ? 
            0x80 >> _bitCount :
            0;
    }
    else
    {
        _startAcknowledge();
        _readData.push(_readByte);
        _bitCount = 0;
        _readByte = 0;
    }

    _bitCount++;
}

void SlowSlaveI2c::_writeDataState()
{
    delayMicroseconds(I2C_SLAVE_DELAY_FOR_SDA_UPDATE);

    if(_bitCount == 0)
    {
        if(_writeData.count())
        {
            _writeByte = _writeData.pop();
        }
        else
        {
            _onSclSync = _idleState;
            return;
        }
    }

    if(_bitCount < 8)
    {
        _writeByte & (0x80 >> _bitCount) ?
            _sdaHigh() :
            _sdaLow();
    }
    else
    {
        _startAcknowledge();
        _bitCount = 0;
    }
    
    _bitCount++;
}

bool SlowSlaveI2c::_sdaChanged()
{
    return _sdaCurrentState != _sdaPreviousState;
}

bool SlowSlaveI2c::_sclFalling()
{
    return (_sclCurrentState != _sclPreviousState)
        && !_sclCurrentState;
}

bool SlowSlaveI2c::_gotStartBit()
{
    return (!_sdaCurrentState)
        && _sclCurrentState
        && _sdaChanged();
}

bool SlowSlaveI2c::_gotStopBit()
{
    return _sdaCurrentState 
        && _sclCurrentState
        && _sdaChanged();
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

void SlowSlaveI2c::_lockLowSclLine()
{
    pinMode(_sclPin, OUTPUT);
}

void SlowSlaveI2c::_releaseSclLine()
{
    pinMode(_sclPin, INPUT);
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