#include "DataConverter.h"

#include "../spi/HydraRF/Structure.h"

#include "IncommingCommunicationFormat.h"
#include "OutgoingCommunicationFormat.h"

IncommingCommunicationFormat DataConverter::translate(struct sCom* rawRfData)
{
    IncommingCommunicationFormat input;
    input.mode = rawRfData->alpha.mode;

    uint8_t forwardThrottle = rawRfData->alpha.moteur.bit.up ? rawRfData->alpha.moteur.bit.speed : 0;
    uint8_t backwardThrottle = rawRfData->alpha.moteur.bit.down ? rawRfData->alpha.moteur.bit.speed : 0;
    input.throttle = forwardThrottle - backwardThrottle;

    uint8_t leftSteer = rawRfData->alpha.moteur.bit.left ? rawRfData->alpha.moteur.bit.speed : 0;
    uint8_t rightSteer = rawRfData->alpha.moteur.bit.right ? rawRfData->alpha.moteur.bit.speed : 0;
    input.steer = (leftSteer - rightSteer) * 0.39269908; // transform received angular velocity in rads/s
    
    input.sonarAngleZ = ((((int)rawRfData->alpha.distance) - 128)*(PI/2.0))/128;
    input.cameraAngleZ = ((((int)rawRfData->alpha.camera.split.rotation) - 128)*(PI/2.0))/128;
    input.cameraAngleY = ((((int)rawRfData->alpha.camera.split.tilt) - 128)*(PI/2.0))/128;

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