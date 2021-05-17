// Author: John-William Lebel, 2021-05-13, creation

#include "RfLessControlTest.h"

#include "../../shared/utils/math/vector/Vector3.h"

#include "../peripheral/i2c/bno055/Bno055.h"
#include "../peripheral/serial/esp_cam/EspCam.h"

#include "../io/output/Outputs.h"

#include "../io/input/sonar/SonarScanner.h"

void RfLessControlTest::execute()
{
    Vector3 desiredOrientation{1, 0, 0};
    Vector3 currentOrientation = Bno055::orientation().front;

    // stupid handling of the bdc motors as a demo
    //Outputs::bdcMotorLeft.setMotorTorque(-desiredOrientation.findRotator(currentOrientation).z*3.2 + Bno055::angularVelocity().z*0.3);
    //Outputs::bdcMotorRight.setMotorTorque(-desiredOrientation.findRotator(currentOrientation).z*3.2 + Bno055::angularVelocity().z*0.3);
    Outputs::bdcMotorLeft.setMotorTorque(-1);

    //servoMotorSonarZ.setMotorAngle(desiredOrientation.findRotator(currentOrientation).z);
    //Outputs::servoMotorSonarZ.setMotorAngle(SonarScanner::getDesiredSonarAngle());
    //Outputs::servoMotorCameraZ.setMotorAngle(desiredOrientation.findRotator(currentOrientation).z);
    ///Outputs::servoMotorCameraY.setMotorAngle(0);

    // handle EspCam sending camera feed over WiFi
    EspCam::enableSendingImagesOverWifi(true);
}