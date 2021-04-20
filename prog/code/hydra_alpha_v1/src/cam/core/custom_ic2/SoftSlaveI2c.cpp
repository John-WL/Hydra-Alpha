// Author: John-William Lebel, 2021-04-17, creation

#include "SoftSlaveI2c.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../../../projectConfig.h"  // for easy on/off debugging

void SoftSlaveI2c::init(uint8_t chipAddress, uint8_t sdaPin, uint8_t sclPin)
{
    serialDebug("soft I2C init");
    _sdaPin = sdaPin;
    _sclPin = sclPin;

    _chipAddress = chipAddress & 0xFE;  // removing the last bit to impose a valid address
    // address 0x00 is not available
    if(_chipAddress == 0x00)
    {
        return;
    }

    pinMode(_sdaPin, INPUT_PULLUP);
    pinMode(_sclPin, INPUT_PULLUP);
    digitalWrite(_sdaPin, LOW); // To use pinMode() function to write data. This way, we aren't triggering the interrupts ourselves.
    _sdaState = digitalRead(_sdaPin);
    _sclState = digitalRead(_sclPin);

    attachInterrupt(digitalPinToInterrupt(_sdaPin), _onSdaChange, CHANGE);
    attachInterrupt(digitalPinToInterrupt(_sclPin), _onSclChange, CHANGE);
}

void IRAM_ATTR SoftSlaveI2c::_onSdaChange()
{
    serialDebug("sda changed");
    // update sda internal state
    _sdaState = !_sdaState;

    // scl state = 1
    if(_sclState)
    {
        // - scl high;
        // - sda transition to high;
        // We have a stop bit.
        if(_sdaState)
        {
            // set the communication mode and sync pin states
            _sdaState = digitalRead(_sdaPin);
            _sclState = digitalRead(_sclPin);
            _communicationState = SoftSlaveI2cCommunicationState::STOP;
            if(_wasReceiving)
            {
                onReceive(_receivedData);
                _receivedData.clear();
            }
        }
        // - scl high;
        // - sda transition to low;
        // We have a start bit.
        else
        {
            _communicationState = SoftSlaveI2cCommunicationState::START;
        }
    }
    // scl low
    else
    {
        // do nothing
    }
}

void IRAM_ATTR SoftSlaveI2c::_onSclChange()
{
    serialDebug("scl changed");
    // update scl internal state
    _sclState = !_sclState;
    
    // - scl transition to high;
    // We have an sda bit sync.
    if(_sclState)
    {
        switch(_communicationState)
        {
            case SoftSlaveI2cCommunicationState::START:
                // reset bit count
                _bitCount = 0;
                // reset the received selection address
                _receivedAddressSelect = 0;
                // make sure sda is an input
                pinMode(_sdaPin, INPUT_PULLUP);
                // change communication state to address reading
                _communicationState = SoftSlaveI2cCommunicationState::READ_ADDRESS;
                break;
            case SoftSlaveI2cCommunicationState::READ_ADDRESS:
                if(_bitCount < 8)
                {
                    // update the received selection address
                    _receivedAddressSelect |= _sdaState << (7-_bitCount);
                    // update the bit count for the next address reading
                    _bitCount++;
                }
                else
                {
                    // reset the bit counter
                    _bitCount = 0;
                    // reading mode
                    if(_receivedAddressSelect == _chipAddress)
                    {
                        _communicationState = SoftSlaveI2cCommunicationState::READ_DATA;
                        _wasReceiving = true;
                    }
                    // writing mode
                    else if(_receivedAddressSelect == _chipAddress | 0x01)
                    {
                        _communicationState = SoftSlaveI2cCommunicationState::WRITE_DATA;
                        _wasReceiving = false;
                    }
                }
                break;
            case SoftSlaveI2cCommunicationState::READ_DATA:
                if(_bitCount < 8)
                {
                    // update the received data
                    _receivedByte |= _sdaState << (7-_bitCount);
                    // update the bit count for the next address reading
                    _bitCount++;
                }
                else
                {
                    // store the received byte
                    _receivedData.push_back(_receivedByte);
                    // reset it for further reads
                    _receivedByte = 0;
                    // reset the bit counter
                    _bitCount = 0;
                }
                break;
            case SoftSlaveI2cCommunicationState::WRITE_DATA:
                break;
            default:
                break;
        }
    }
    // scl state = 0
    else
    {
        switch(_communicationState)
        {
            // acknowledge handling
            case SoftSlaveI2cCommunicationState::WRITE_DATA:
                if(_bitCount == 8)
                {
                    if(_sendsAcknowledges) pinMode(_sdaPin, OUTPUT);
                }
                else if(_bitCount == 0)
                {
                    if(_sendsAcknowledges) pinMode(_sdaPin, INPUT_PULLUP);
                }
                // get byte data from the data transmitter vector
                if(_bitCount == 0)
                {
                    if(_transmitData.size() > 0)
                    {
                        _transmitData = onRequest();
                        _transmitByte = _transmitData[_transmitData.size() - 1];
                        _transmitData.erase(_transmitData.end() - 1);
                    }
                    else
                    {
                        _transmitByte = 0xFF;
                    }
                }
                else if(_bitCount < 8)
                {
                    // update the sda pin to transmit data
                    _transmitByte & (1 << (7-_bitCount)) ?
                        pinMode(_sdaPin, INPUT_PULLUP) :
                        pinMode(_sdaPin, OUTPUT);
                    // update the bit count for the next address sending
                    _bitCount++;
                }
                else
                {
                    // reset the bit counter
                    _bitCount = 0;
                }
                break;
            case SoftSlaveI2cCommunicationState::READ_ADDRESS:
            case SoftSlaveI2cCommunicationState::READ_DATA:
                if(_bitCount == 8)
                {
                    if(_sendsAcknowledges) pinMode(_sdaPin, OUTPUT);
                }
                else if(_bitCount == 0)
                {
                    if(_sendsAcknowledges) pinMode(_sdaPin, INPUT_PULLUP);
                }
                break;
        }
    }
}

uint8_t SoftSlaveI2c::_chipAddress{0};
uint8_t SoftSlaveI2c::_sdaPin{0};
uint8_t SoftSlaveI2c::_sclPin{0};
bool SoftSlaveI2c::_sdaState{false};
bool SoftSlaveI2c::_sclState{false};

uint8_t SoftSlaveI2c::_receivedAddressSelect{0};
uint8_t SoftSlaveI2c::_communicationState{SoftSlaveI2cCommunicationState::IDLE};
uint8_t SoftSlaveI2c::_bitCount{0};

bool SoftSlaveI2c::_sendsAcknowledges{false};

uint8_t SoftSlaveI2c::_receivedByte{0};
uint8_t SoftSlaveI2c::_transmitByte{0};
std::vector<uint8_t> SoftSlaveI2c::_receivedData{32};
std::vector<uint8_t> SoftSlaveI2c::_transmitData{32};

bool SoftSlaveI2c::_wasReceiving{false};