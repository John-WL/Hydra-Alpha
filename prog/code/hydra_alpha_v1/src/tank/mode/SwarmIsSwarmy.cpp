// Author: John-William Lebel, 2021-04-08, creation

#include "SwarmIsSwarmy.h"

#include "Arduino.h"

#include "../io/output/Outputs.h"

#include "../../shared/utils/math/vector/Vector3.h"
#include "../../shared/utils/math/vector/Vector2.h"

#include "FunctioningMode.h"
#include "ListeningToYourCommands.h"

#include "../peripheral/protocol_format/IncommingCommunicationFormat.h"

#include "../peripheral/serial/esp_cam/EspCam.h"

void SwarmIsSwarmy::execute(IncommingCommunicationFormat remoteInput)
{
    ListeningToYourCommands::execute(
        _rectangleInCameraFrameExists() ? 
            _followState(remoteInput) :
            _searchState(remoteInput)
    );
}

IncommingCommunicationFormat SwarmIsSwarmy::_followState(IncommingCommunicationFormat remoteInput)
{
    // finding the center of where the other tank is in our image
    Vector2 middlePointOfRectangle = EspCam::rectangleOfTankOmegaInFrame->findCenter();

    // shifting the center to get signed values
    Vector2 shiftedMiddlePointOfRectangle = middlePointOfRectangle - Vector2{320/2, 240/2};

    static const float radsPerPixel = (62 * (PI/180))/320;

    // scale so the values are in radians/pixel instead
    Vector2 rotationAmounts = shiftedMiddlePointOfRectangle * radsPerPixel;

    // create rotator vectors
    Vector3 frontVector = Vector3{1, 0, 0};
    Vector3 rotatorZ = Vector3{0, 0, 1} * rotationAmounts.x;
    Vector3 rotatorY = Vector3{0, 1, 0} * rotationAmounts.y;

    // perform the initial rotation to find the orientation of the vector in the camera's perspective
    Vector3 approximateOrientationInCameraPerspective = frontVector
        .rotate(rotatorZ)
        .rotate(rotatorY);

    // find rotator vectors that correspond to servo motor angles
    Vector3 rotatorServoZ = Vector3{0, 0, 1} * Outputs::servoMotorCameraZ.getMotorAngle();
    Vector3 rotatorServoY = Vector3{0, 1, 0} * Outputs::servoMotorCameraY.getMotorAngle();

    // rotate the vector that was in camera perspective using the servo motor rotators to find its orientation in local coordinates
    Vector3 offsetedOtherTankDirection = approximateOrientationInCameraPerspective
        .rotate(rotatorServoZ)
        .rotate(rotatorServoY);

    // this function takes in the distance between 2 corners of the rectangle, and outputs an approximate distance
    float angleOfOtherTankInCameraFrame = EspCam::rectangleOfTankOmegaInFrame->diagonalSize() * radsPerPixel/2;
    float approximateDistanceFromOtherTank = APPROXIMATE_AVERAGE_LENGTH_OF_OTHER_TANK / tan(angleOfOtherTankInCameraFrame);

    // this vector represents the position of the other tank from the camera's pivot point
    Vector3 offsetedOtherTankPosition = offsetedOtherTankDirection * approximateDistanceFromOtherTank;




    // calculate the input variable (and optionnaly add pid controllers and what not!)
    uint8_t mode = remoteInput.mode;
    float throttle = approximateDistanceFromOtherTank - DESIRED_DITANCE_FROM_TARGET;
    float steer = offsetedOtherTankPosition.findRotator(Vector3{1, 0, 0}).z;
    float sonarAngleZ = 0;
    float cameraAngleZ = Outputs::servoMotorCameraZ.getMotorAngle() + rotationAmounts.x;
    float cameraAngleY = Outputs::servoMotorCameraY.getMotorAngle() + rotationAmounts.y;
    bool wiFiCameraEnabled = remoteInput.wiFiCameraEnabled;
    return IncommingCommunicationFormat
    {
        mode,
        throttle,
        steer,
        sonarAngleZ,
        cameraAngleZ,
        cameraAngleY,
        wiFiCameraEnabled
    };
}

IncommingCommunicationFormat SwarmIsSwarmy::_searchState(IncommingCommunicationFormat remoteInput)
{
    // The input state object.
    // This peculiar configuration of the input struct makes the tank rotate on 
    // itself on the Z axis until it finds the other tank, after which it changes
    // of state, and starts to follow the other tank instead.
    // It's basically a rudimentary search mode.
    return IncommingCommunicationFormat
    {
        remoteInput.mode,               // mode
        0,                              // throttle
        1,                              // steer
        0,                              // sonar Z
        0,                              // camera Z
        0,                              // camera Z
        remoteInput.wiFiCameraEnabled   // wiFiCameraEnabled
    };
}

bool SwarmIsSwarmy::_rectangleInCameraFrameExists()
{
    // that's a pointer. Returns false if nullpointer
    return EspCam::rectangleOfTankOmegaInFrame;
}

IncommingCommunicationFormat _adjustOutputWithSensorData(IncommingCommunicationFormat input)
{
    // for now, don't adjust anything...
    // we're gonna handle the sensor data at some point, but just not for now...
    return input;
}