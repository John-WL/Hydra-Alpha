// Author: John-William Lebel, 2021-04-08, creation

#include "ListeningToYourCommands.h"

#include "Arduino.h"

#include "../io/output/Outputs.h"

#include "FunctioningMode.h"

#include "../peripheral/protocol_format/IncommingCommunicationFormat.h"
#include "../peripheral/protocol_format/OutgoingCommunicationFormat.h"

#include "../peripheral/slow_i2c/esp_cam/EspCam.h"

#include "../io/input/sonar/Sonar.h"
#include "../io/input/battery/BatteryVoltageSensor.h"

void ListeningToYourCommands::execute(IncommingCommunicationFormat input)
{
    // update bdc motors
    Outputs::bdcMotorLeft.setMotorTorque((int8_t)(32*(input.throttle - input.steer)));
    Outputs::bdcMotorRight.setMotorTorque((int8_t)(32*(input.throttle + input.steer)));

    // udate the servo motors
    Outputs::servoMotorCameraZ.setMotorAngle(input.cameraAngleZ);
    Outputs::servoMotorCameraY.setMotorAngle(input.cameraAngleY);
    Outputs::servoMotorSonarZ.setMotorAngle(input.sonarAngleZ);

    // handle EspCam sending camera feed over WiFi
    EspCam::enableSendingImagesOverWifi(input.wiFiCameraEnabled);

    // update the functionning mode
    FunctioningMode::set(input.mode);

    // computing the checksum (cast all non-uint8_t variables)
    uint8_t checksum = 
        input.mode
        + (uint8_t)Sonar::measuredDistance
        + (uint8_t)BatteryVoltageSensor::getValue()
        + 0;    // WiFi signal strength, not yet implemented
    OutgoingCommunicationFormat output
    {
        input.mode,
        Sonar::measuredDistance,
        BatteryVoltageSensor::getValue(),
        0, // WiFi signal strength. For this to be implemented, we need to add a command to the EspCam device protocol
        checksum
    };

    // !!!!!
    // make it so we send the output variable back to the RF communication

    // !!!!!
}