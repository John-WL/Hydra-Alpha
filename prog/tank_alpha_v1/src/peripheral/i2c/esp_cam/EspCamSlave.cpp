// Author: John-William Lebel, 2021-04-15, creation

#include "EspCamSlave.h"

#include "Arduino.h"

#include "../../../mode/FunctioningMode.h"

#include "Vector.h"

void EspCamSlave::init()
{
    pinMode(ESP_CAM_HARDWARE_RESET_PIN, INPUT);
    digitalWrite(ESP_CAM_HARDWARE_RESET_PIN, LOW);
    _requestHandlingOfSendingImagesOverWiFi(false);
}

void EspCamSlave::update()
{
    _updateRectangleRequest();
    _updateWiFiCameraRequest();
}

void EspCamSlave::enableSendingImagesOverWifi(bool isSendingImagesOverWiFi)
{
    _isSendingImagesOverWiFi = isSendingImagesOverWiFi;
}

void EspCamSlave::_updateWiFiCameraRequest()
{
    // did the image over wifi state change?
    if(_isSendingImagesOverWiFi != _wasSendingImagesOverWiFi)
    {
        // reset the "derivative"
        _wasSendingImagesOverWiFi = _isSendingImagesOverWiFi;
        // send to the slave the new "image over wifi" state
        _requestHandlingOfSendingImagesOverWiFi(_isSendingImagesOverWiFi);
    }
}

void EspCamSlave::_requestHandlingOfSendingImagesOverWiFi(bool isSendingData)
{
    // send the request...
    std::vector<unsigned char> data{};
    data.push_back(0x00);                           // WiFi camera command id
    data.push_back(isSendingData ? 0x80 : 0x00);    // set the state depending on what was passed as parameter
    _i2cDevice.transmit(data);                      // transmit that

    // gather data
    std::vector<unsigned char> receivedData = _i2cDevice.receive(1); // receive 1 byte

    // check for weird errors
    if(receivedData.size() != 1)
    {
        Serial.println("Can't gather EspCam WiFi status.");
        return;
    }

    // handle the received status
    switch(receivedData[0])
    {
        case ESP_CAM_OK_WIFI_STATUS:
        case ESP_CAM_SEARCHING_WIFI_STATUS:
            break;
        case ESP_CAM_FAILURE_WIFI_STATUS:
            Serial.println("Hard reseting EspCam because the device couldn't find any WiFi access point.");
            _hardReset();
            break;
        default:
            // wtf??
            Serial.println("Gathered EspCam WiFi status is not valid.");
            Serial.print("Value should be between 0 and 2, but we received \"");
            Serial.print(receivedData[0]);
            Serial.println("\" instead.\n");
            break;
    }

}

void EspCamSlave::_hardReset()
{
    pinMode(ESP_CAM_HARDWARE_RESET_PIN, OUTPUT);    // from 3-state to low-level output
    digitalWrite(ESP_CAM_HARDWARE_RESET_PIN, LOW);  // just making sure...

    delayMicroseconds(80);  // at least 50µS according to datasheet

    pinMode(ESP_CAM_HARDWARE_RESET_PIN, INPUT);     // back to 3-state again
}

void EspCamSlave::_updateRectangleRequest()
{
    if(FunctioningMode::get() == SWARM_IS_SWARMY_FUNCTIONING_MODE)
    {
        unsigned char rectangleStatus = _requestStatusOfRectangleGeneration();
        switch(rectangleStatus)
        {
            case ESP_CAM_RECTANGLE_IDLE_GENERATION_STATUS:
                // if the EspCam is not baking our "cake" rectangle,
                // then request a rectangle
                _requestGenerationOfRectangle();
                break;
            case ESP_CAM_RECTANGLE_PENDING_GENERATION_STATUS:
                // If the EspCam IS curently baking our cake,
                // then get outa here. Nothing to see yet! 
                break;
            case ESP_CAM_RECTANGLE_BAKED_GENERATION_STATUS:
                // If our cake is ready, then go get it!
                rectangleOfTankOmegaInFrame = _requestRectangleOfTankOmegaInFrame();
                break;
            default:
                // Got some weird transmission going on...
                // Check your I2C drivers man.
                Serial.println("Our rectangle is not cooking very well...");
                Serial.print("We received a rectangle generation status of value \"");
                Serial.print(rectangleStatus);
                Serial.println("\"\n");
        }
    }
}

unsigned char EspCamSlave::_requestStatusOfRectangleGeneration()
{
    // send the request...
    std::vector<unsigned char> data{};
    data.push_back(0x01);                           // Rectangle status request command id
    _i2cDevice.transmit(data);                      // transmit that

    // gather data
    std::vector<unsigned char> receivedData = _i2cDevice.receive(1); // receive 1 byte

    // check for weird errors
    if(receivedData.size() != 1)
    {
        Serial.println("Can't gather rectangle generation status.");
        return ESP_CAM_RECTANGLE_INVALID_GENERATION_STATUS;
    }

    // return the status
    return receivedData[0];
}

void EspCamSlave::_requestGenerationOfRectangle()
{
    // send the request...
    std::vector<unsigned char> data{};
    data.push_back(0x02);                           // Rectangle generation request command id
    _i2cDevice.transmit(data);                      // transmit that
}

Rectangle2* EspCamSlave::_requestRectangleOfTankOmegaInFrame()
{
    // send the request...
    std::vector<unsigned char> data{};
    data.push_back(0x03);                           // Rectangle gathering request command id
    _i2cDevice.transmit(data);                      // transmit that

    // gather data
    std::vector<unsigned char> receivedData = _i2cDevice.receive(6); // receive 6 bytes

    // check for weird errors
    if(receivedData.size() != 6)
    {
        Serial.println("Can't gather rectangle info.");
        return nullptr;
    }

    // make sure to delete the last ref we had before doing a new
    if(rectangleOfTankOmegaInFrame != nullptr)
    {
        delete rectangleOfTankOmegaInFrame;
    }

    // parse the coordinates and return
    unsigned int upperLeftX = ((receivedData[1] & 0x0F) << 8) | receivedData[0];
    unsigned int upperLeftY = ((receivedData[2] << 4) | ((receivedData[1] & 0xF0) >> 4));
    unsigned int lowerRightX = ((receivedData[4] & 0x0F) << 8) | receivedData[3];
    unsigned int lowerRightY = ((receivedData[5] << 4) | ((receivedData[4] & 0xF0) >> 4));
    return new Rectangle2
    {
        Vector2
        {
            upperLeftX, 
            upperLeftY
        }, 
        Vector2
        {
            lowerRightX, 
            lowerRightY
        }
    };
}

Rectangle2* EspCamSlave::rectangleOfTankOmegaInFrame = nullptr;

bool EspCamSlave::_isSendingImagesOverWiFi = false;
bool EspCamSlave::_wasSendingImagesOverWiFi = false;

I2cDevice EspCamSlave::_i2cDevice{I2C_ESP_CAM_SLAVE_ADDRESS};