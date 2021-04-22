// Author: John-William Lebel, 2021-04-16, creation

#ifndef ALPHA_TO_REMOTE_COMMUNICATION_FORMAT_H
#define ALPHA_TO_REMOTE_COMMUNICATION_FORMAT_H

#define ALPHA_TO_REMOTE_LISTENING_TO_COMMAANDS_MODE 0
#define ALPHA_TO_REMOTE_SWARM_MODE 1

#include "Arduino.h"

typedef struct
{
    uint8_t mode;
    uint32_t distanceSonar;
    uint8_t batteryLevel;
    int8_t signalStrength;
    uint8_t checkSum;
} OutgoingCommunicationFormat;

#endif