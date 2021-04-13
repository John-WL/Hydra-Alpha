// Author: John-William Lebel, 2021-04-11, creation

#include "I2cProtocol.h"

#include "../../utils/timer/TimerMicros.h"

void I2cProtocol::init()
{
    Wire.begin();
}

void I2cProtocol::transmit(unsigned char deviceAddress, unsigned char* data, unsigned char dataLength)
{
    Wire.beginTransmission(deviceAddress & ~0x01);
    for(unsigned char i = 0; i < dataLength; i++)
    {
        Wire.write(data[i]);
    }
    Wire.endTransmission();
}

unsigned char* I2cProtocol::receive(unsigned char deviceAddress, unsigned char dataLength)
{
    // receiving array
    static unsigned char dataReceived[I2C_RECEIVE_MAX_MEMORY_USAGE]{};

    // request data
    Wire.requestFrom(deviceAddress, dataLength);

    // useful variables
    transmissionDone = false;
    unsigned char amountOfBytesReceived = 0;
    // This timer ends the reception
    // if we reached the max timeout.
    // We still return the bytes we were able to receive. 
    TimerMicros transmissionTimeoutTimer
    {
        I2C_RECEIVE_TIMEOUT_MICROSECONDS,
        []()
        {
            I2cProtocol::endReception();
        }
    };

    // stay here until we receive all the bytes or 
    // reach the timeout limit
    while(!transmissionDone)
    {
        // if we received a byte
        if(Wire.available())
        {
            // assign the received byte to the next array index
            dataReceived[amountOfBytesReceived] = Wire.read();
            amountOfBytesReceived++;
        }
        // have we received all the bytes?
        transmissionDone = (amountOfBytesReceived >= dataLength);
        // did we reach the timeout limit?
        transmissionTimeoutTimer.update();
    }

    return dataReceived;
}

void I2cProtocol::endReception()
{
    transmissionDone = true;
}

bool I2cProtocol::transmissionDone = true;