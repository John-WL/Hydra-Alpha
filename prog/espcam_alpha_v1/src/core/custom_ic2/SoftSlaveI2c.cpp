// Author: John-William Lebel, 2021-04-17, creation

#include "SoftSlaveI2c.h"

#include "Arduino.h"

#include "Vector.h"

SoftI2cSlave::SoftI2cSlave(uint8_t chipAddress, uint8_t sdaPin, uint8_t sclPin) :
    _receivedAddressSelect{0},
    _sdaPin{sdaPin},
    _sclPin{sclPin},
    _communicationState{SoftI2cSlaveCommunicationState::STOP},
    _bitCount{0},
    _sendsAcknowledges{false},
    _receivedByte{0},
    _receivedData{},
    _transmitByte{0},
    _transmitData{}
{
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
    attachInterrupt(digitalPinToInterrupt(_sdaPin), this->_onSdaChange, CHANGE);
    attachInterrupt(digitalPinToInterrupt(_sclPin), this->_onSclChange, CHANGE);
}

void IRAM_ATTR SoftI2cSlave::_onSdaChange()
{
    // update sda internal state
    _sdaState = !_sdaState;

    // scl state = 1
    if(_sclState)
    {
        // set the communication mode and sync pin states
        if(_sdaState)
        {
            _sdaState = digitalRead(_sdaPin);
            _sclState = digitalRead(_sclPin);
            _communicationState = SoftI2cSlaveCommunicationState::STOP;
            _transmitData = generateDataToTransmit(_receivedData);
            _receivedData.clear();
        }
        else
        {
            _communicationState = SoftI2cSlaveCommunicationState::START;
        }
    }
    // scl state = 0
    else
    {
        // do nothing
    }
}

void IRAM_ATTR SoftI2cSlave::_onSclChange()
{
    // update scl internal state
    _sclState = !_sclState;
    
    // scl state = 1
    if(_sclState)
    {
        switch(_communicationState)
        {
            case SoftI2cSlaveCommunicationState::START:
                // reset bit count
                _bitCount = 0;
                // reset the received selection address
                _receivedAddressSelect = 0;
                // make sure sda is an input
                pinMode(_sdaPin, INPUT_PULLUP);
                // change communication state to address reading
                _communicationState = SoftI2cSlaveCommunicationState::READ_ADDRESS;
                break;
            case SoftI2cSlaveCommunicationState::READ_ADDRESS:
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
                        _communicationState = SoftI2cSlaveCommunicationState::READ_DATA;
                    }
                    // writing mode
                    else if(_receivedAddressSelect == _chipAddress | 0x01)
                    {
                        _communicationState = SoftI2cSlaveCommunicationState::WRITE_DATA;
                    }
                }
                break;
            case SoftI2cSlaveCommunicationState::READ_DATA:
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
            case SoftI2cSlaveCommunicationState::WRITE_DATA:
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
            case SoftI2cSlaveCommunicationState::WRITE_DATA:
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
                        _transmitByte = _transmitData[_transmitData.size() - 1];
                        _transmitData.erase(_transmitData.end() - 1);
                    }
                    else
                    {
                        _transmitByte = 0;
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
            case SoftI2cSlaveCommunicationState::READ_ADDRESS:
            case SoftI2cSlaveCommunicationState::READ_DATA:
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
