#include "DataConverter.h"

#include "../spi/HydraRF/Structure.h"

#include "IncommingCommunicationFormat.h"
#include "OutgoingCommunicationFormat.h"

IncommingCommunicationFormat DataConverter::translate(struct sCom* rawRfData)
{
    IncommingCommunicationFormat input;
    input.mode = rawRfData->alpha.mode;

    float movementSpeed = rawRfData->alpha.moteur.bit.speed/16.0;

    float forwardThrottle = rawRfData->alpha.moteur.bit.up ? movementSpeed : 0;
    float backwardThrottle = rawRfData->alpha.moteur.bit.down ? movementSpeed : 0;
    input.throttle = forwardThrottle - backwardThrottle;

    float leftSteer = rawRfData->alpha.moteur.bit.left ? movementSpeed : 0;
    float rightSteer = rawRfData->alpha.moteur.bit.right ? movementSpeed : 0;
    input.steer = (leftSteer - rightSteer);
    
    // Converting to radians... 
    // Data comming from remote is 8 bits, so from 0 to 255.
    // -128, now it's from -128 to 127.
    // /128, now it's from -1.0 to 0.9921875.
    // *PI/2, now it's in radians.
    float factorToConvertFromByteToRadians = 0.00390625 * PI; // PI / (2 * 128)
    input.sonarAngleZ = (((int)rawRfData->alpha.distance) - 128) * factorToConvertFromByteToRadians;
    input.cameraAngleZ = (((int)rawRfData->alpha.camera.split.rotation) - 128) * factorToConvertFromByteToRadians;
    input.cameraAngleY = (((int)rawRfData->alpha.camera.split.tilt) - 128) * factorToConvertFromByteToRadians;

    input.wiFiCameraEnabled = true;

    return input;
}

void DataConverter::translate(OutgoingCommunicationFormat* output, AlphaToRemoteCommunicationFormat* convertedOutput)
{
    convertedOutput->mode = output->mode;
    convertedOutput->distanceSonar.split.lsb = output->distanceSonar;
    convertedOutput->distanceSonar.split.msb = output->distanceSonar >> 8;
    convertedOutput->batteryLevel = output->batteryLevel;
    //convertedOutput->signalStrength = output->signalStrength;

    uint8_t checkSum ;
}