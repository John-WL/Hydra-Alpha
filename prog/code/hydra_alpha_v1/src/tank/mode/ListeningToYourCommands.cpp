// Author: John-William Lebel, 2021-04-08, creation

#include "ListeningToYourCommands.h"

#include "Arduino.h"

#include "../io/output/Outputs.h"

#include "FunctioningMode.h"

#include "../peripheral/protocol_format/IncommingCommunicationFormat.h"
#include "../peripheral/protocol_format/OutgoingCommunicationFormat.h"

#include "../peripheral/serial/esp_cam/EspCam.h"

#include "../io/input/sonar/Sonar.h"
#include "../io/input/battery/BatteryVoltageSensor.h"

#include "../peripheral/protocol_format/DataConverter.h"
#include "../peripheral/spi/HydraRF/HydraRF.h"

void ListeningToYourCommands::execute(IncommingCommunicationFormat input)
{
    // update bdc motors
    Outputs::bdcMotorLeft.setMotorTorque(32*(input.throttle - input.steer));
    Outputs::bdcMotorRight.setMotorTorque(32*(input.throttle + input.steer));

    // udate the servo motors
    Outputs::servoMotorCameraZ.setMotorAngle(input.cameraAngleZ);
    Outputs::servoMotorCameraY.setMotorAngle(input.cameraAngleY);
    Outputs::servoMotorSonarZ.setMotorAngle(input.sonarAngleZ);

    // handle EspCam sending camera feed over WiFi
    EspCam::enableSendingImagesOverWifi(input.wiFiCameraEnabled);

    // update the functionning mode
    FunctioningMode::set(input.mode);

    OutgoingCommunicationFormat output{};
    output.mode = input.mode;
    output.distanceSonar = Sonar::measuredDistance;
    output.batteryLevel = BatteryVoltageSensor::getValue();
    output.signalStrength = 0;

    // TrameAlpha is defined in "HydraRF.h"
    DataConverter::translate(&output, &TrameAlpha);
}