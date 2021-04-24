// Author: John-William Lebel, 2021-04-15, creation

#include "EspCam.h"

#include "Arduino.h"

#include "../../../mode/FunctioningMode.h"

#include "Vector.h"

#include "../../../../shared/peripheral/spare_serial/SerialMaster.h"

void EspCam::init()
{
    SerialMaster::begin(115200);
    _requestHandlingOfSendingImagesOverWiFi(false);
}

void EspCam::update()
{
    _updateRectangleRequest();
    _updateWiFiCameraRequest();
}

void EspCam::enableSendingImagesOverWifi(bool isSendingImagesOverWiFi)
{
    _isSendingImagesOverWiFi = isSendingImagesOverWiFi;
}

void EspCam::_updateWiFiCameraRequest()
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

void EspCam::_requestHandlingOfSendingImagesOverWiFi(bool isSendingData)
{
    // send...
    std::vector<uint8_t> dataToSend{};
    dataToSend.push_back(0x00);                                      // WiFi camera command id
    dataToSend.push_back(isSendingData ? 0x80 : 0x00);               // set the state depending on what was passed as parameter
    SerialMaster::send(dataToSend); // transmit that
}

void EspCam::_updateRectangleRequest()
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

unsigned char EspCam::_requestStatusOfRectangleGeneration()
{
    // send...
    std::vector<uint8_t> dataToSend{};
    dataToSend.push_back(0x01);                                      // Rectangle status request command id
    SerialMaster::send(dataToSend); // transmit that

    // request...
    std::vector<uint8_t> receivedData = SerialMaster::receive(1);

    // check for weird errors
    if(receivedData.size() != 1)
    {
        Serial.println("Can't gather rectangle generation status.");
        Serial.println("In other words, you suck at transmitting data.");
        return ESP_CAM_RECTANGLE_INVALID_GENERATION_STATUS;
    }

    // return the status
    return receivedData[0];
}

void EspCam::_requestGenerationOfRectangle()
{
    // send...
    std::vector<uint8_t> dataToSend{};
    dataToSend.push_back(0x02);                                      // Rectangle generation request command id
    SerialMaster::send(dataToSend); // transmit that
}

Rectangle2* EspCam::_requestRectangleOfTankOmegaInFrame()
{
    // send...
    std::vector<uint8_t> dataToSend{};
    dataToSend.push_back(0x03);                                      // Rectangle gathering request command id
    SerialMaster::send(dataToSend); // transmit that

    // request...
    std::vector<uint8_t> receivedData = SerialMaster::receive(7);    // request 7 bytes

    // check for weird errors
    if(receivedData.size() == 0)
    {
        Serial.println("Can't gather rectangle info:");
        Serial.println("Slave device violated the protocol.");
        return nullptr;
    }

    if((receivedData[0] & 0x80) == 0)
    {
        // no rectangles were found
        return nullptr;
    }
    
    // check for weird errors
    if(receivedData.size() != 7)
    {
        Serial.println("Can't gather rectangle info:");
        Serial.println("Slave data loss.");
        return nullptr;
    }

    // make sure to delete the last ref we had before making a new
    if(rectangleOfTankOmegaInFrame != nullptr)
    {
        delete rectangleOfTankOmegaInFrame;
    }

    // parse the coordinates and return
    unsigned int upperLeftX =   ((((unsigned int)receivedData[1]) & 0x0F) << 8) | (unsigned int)receivedData[0];
    unsigned int upperLeftY =   (((unsigned int)receivedData[2]) << 4)          | ((((unsigned int)receivedData[1]) & 0xF0) >> 4);
    unsigned int lowerRightX =  ((((unsigned int)receivedData[4]) & 0x0F) << 8) | (unsigned int)receivedData[3];
    unsigned int lowerRightY =  (((unsigned int)receivedData[5]) << 4)          | ((((unsigned int)receivedData[4]) & 0xF0) >> 4);
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

Rectangle2* EspCam::rectangleOfTankOmegaInFrame = nullptr;

bool EspCam::_isSendingImagesOverWiFi = false;
bool EspCam::_wasSendingImagesOverWiFi = false;