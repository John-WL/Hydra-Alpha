// Author: John-William Lebel, 2021-04-16, creation

#ifndef ALPHA_TO_REMOTE_COMMUNICATION_FORMAT_H
#define ALPHA_TO_REMOTE_COMMUNICATION_FORMAT_H

#define ALPHA_TO_REMOTE_LISTENING_TO_COMMAANDS_MODE 0
#define ALPHA_TO_REMOTE_SWARM_MODE 1

typedef struct
{
    unsigned char batteryLevel;
    unsigned int distanceSonar;
    unsigned char mode;
    unsigned char checkSum;
} AlphaToRemoteCommunicationFormat;

#endif