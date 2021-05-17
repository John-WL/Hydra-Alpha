// Author: John-William Lebel, 2021-04-15, creation

#ifndef INCOMMING_COMMUNICATION_FORMAT_H
#define INCOMMING_COMMUNICATION_FORMAT_H

#include "Arduino.h"

typedef struct
{
    uint8_t mode;
    float throttle;
    float steer;
    float sonarAngleZ;
    float cameraAngleZ;
    float cameraAngleY;
    bool wiFiCameraEnabled;
} IncommingCommunicationFormat;

#endif