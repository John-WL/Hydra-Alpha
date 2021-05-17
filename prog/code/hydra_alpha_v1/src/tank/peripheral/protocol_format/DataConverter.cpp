#include "DataConverter.h"

#include "../spi/HydraRF/Structure.h"

#include "IncommingCommunicationFormat.h"
#include "OutgoingCommunicationFormat.h"

#include "../../io/output/Outputs.h"

IncommingCommunicationFormat DataConverter::translate(struct sCom* rawRfData)
{
    IncommingCommunicationFormat input;
    input.mode =              rawRfData->alpha.mode.bit.ctrl;
    input.wiFiCameraEnabled = rawRfData->alpha.mode.bit.wifi;

    float movementSpeed = rawRfData->alpha.moteur.bit.speed * 0.25;

    float forwardThrottle =  rawRfData->alpha.moteur.bit.up   ? movementSpeed : 0;
    float backwardThrottle = rawRfData->alpha.moteur.bit.down ? movementSpeed : 0;
    input.throttle = forwardThrottle - backwardThrottle;

    float leftSteer =  rawRfData->alpha.moteur.bit.left  ? movementSpeed : 0;
    float rightSteer = rawRfData->alpha.moteur.bit.right ? movementSpeed : 0;
    input.steer = leftSteer - rightSteer;

    input.sonarAngleZ =  ((rawRfData->alpha.servo.split.distance < 2 ? rawRfData->alpha.servo.split.distance : -1) * 0.001) + Outputs::servoMotorSonarZ.getMotorAngle();
    input.cameraAngleZ = ((rawRfData->alpha.servo.split.rotation < 2 ? rawRfData->alpha.servo.split.rotation : -1) * 0.001) + Outputs::servoMotorCameraZ.getMotorAngle();
    input.cameraAngleY = ((rawRfData->alpha.servo.split.tilt     < 2 ? rawRfData->alpha.servo.split.tilt     : -1) * 0.001) + Outputs::servoMotorCameraY.getMotorAngle();

    return input;
}

void DataConverter::translate(OutgoingCommunicationFormat* output, AlphaToRemoteCommunicationFormat* convertedOutput)
{
    convertedOutput->mode.bit.ctrl =           output->mode;
    convertedOutput->distanceSonar.split.lsb = output->distanceSonar;
    convertedOutput->distanceSonar.split.msb = output->distanceSonar >> 8;
    convertedOutput->batteryLevel =            output->batteryLevel;
}