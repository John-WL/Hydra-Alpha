// Author: John-William Lebel, 2021-04-13, creation

#include "Sonar.h"

#include "Arduino.h"

void Sonar::init(void (*callback)(long))
{
    // this is called when we have a response of our sonar
    _callback = callback;

    // setup IOs
    pinMode(SONAR_TRIG_PIN, OUTPUT);
    pinMode(SONAR_ECHO_PIN, INPUT);

    // make sure trig is low
    digitalWrite(SONAR_TRIG_PIN, LOW);

    // interrupt to handle sonar responses
    attachInterrupt(digitalPinToInterrupt(SONAR_ECHO_PIN), onEchoReceive, CHANGE);
}

// a better implementation would be to use timers to
// set back to "low" the ouput level of the trig pin
// after 10µs
void Sonar::requestUpdate()
{
    // Reset the request state if
    // the timeout is reached.
    // The request was probably lost
    // or took too long.
    handlePotentialTimeout();

    // Get out of the request if
    // we already requested.
    // Don't request again if we
    // are already waiting for a
    // response.
    if(_waitingForReception)
    {
        return;
    }

    // send a pulse request to the sonar
    digitalWrite(SONAR_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_TRIG_PIN, LOW);

    // save the time of request
    _timeOfRequest = micros();

    // make sure to remember that
    // we just requested
    _waitingForReception = true;
}

// This function is an interrupt. 
// Therefore, the callback function MUST 
// be light-weight and should run as fast
// as possible; we are halting the
// main execution here. 
void IRAM_ATTR Sonar::onEchoReceive()
{
    // get out of the interrupt if:
    // 1) the timeout is reached (in which case we also reset the request state to false);
    // 2) we didn't request anything to begin with.
    handlePotentialTimeout();
    if(!_waitingForReception)
    {
        return;
    }

    // get the amount of time the sound wave traveled in air
    long timeOfReception = micros();
    _duration = micros() - _timeOfRequest;

    // the callback is called when new data is received
    _callback(_duration * SONAR_MICROSECONDS_TO_MM_FACTOR);

    // set the request state to false
    _waitingForReception = false;
}

void Sonar::handlePotentialTimeout()
{
    if(micros() > _timeOfRequest + SONAR_RECEPTION_TIMEOUT_MICROSECONDS)
    {
        _waitingForReception = false;
    }
}

int32_t Sonar::measuredDistance{};

void (*Sonar::_callback)(long) = {};

bool Sonar::_waitingForReception = false;
long Sonar::_timeOfRequest = 0;
long Sonar::_duration = 0;