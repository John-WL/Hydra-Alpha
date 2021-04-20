// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "QueueArray.h"
#include "Vector.h"

//#include "esp_camera.h"

#include "../shared/core/Esp32DualCore.h"

//#include "src/peripheral/camera_sensor/CameraSensor.h"
//#include "src/peripheral/wifi_client_hydra/WiFiClientHydra.h"
//#include "src/peripheral/tank_alpha/TankAlpha.h"

#include "core/slow_slave_i2c/SlowSlaveI2c.h"
#include "core/slow_master_i2c/SlowMasterI2c.h"
//#include "Wire.h"

#include "../troubleshoot_and_debug/i2c_scanner/I2cScanner.h"

void SlowSlaveI2c::onReceive(QueueArray<uint8_t>& data)
{
    Serial.print("Slave received ");
    Serial.print(data.count());
    Serial.println(" byte(s).");

    while(data.count())
    {
        uint8_t byte = data.pop();
        Serial.println(byte);
    }
}

void SlowSlaveI2c::onRequest(QueueArray<uint8_t>& data)
{
    data.push(5);
    data.push(18);
    data.push(34);
    data.push(48);
    data.push(165);
    data.push(238);

    Serial.print("Transmitting ");
    Serial.print(data.count());
    Serial.println(" byte(s)...");
}

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    //Serial.setDebugOutput(true);

    // put your WiFi sender implementation in the brackets
    //WiFiClientHydra::init();
    //CameraSensor::init(WiFiClientHydra::sendDataToRemote);
    //TankAlpha::init();



    /*Serial.println("Initializing hard master I2C...\n");
    Wire.begin();
    delay(1000);
    Serial.println("Initialized.\n\n");*/

    Esp32DualCore::init();

    Serial.println("Initializing soft master I2C...\n");
    SlowMasterI2c::init(26, 25);
    delay(1000);
    Serial.println("Initialized.\n\n");

    Serial.println("Initializing soft slave I2C...\n");
    SlowSlaveI2c::init(76, 33, 32);
    delay(1000);
    Serial.println("Initialized.\n\n");

    //I2cScanner::init();
}

void loop()
{
    //CameraSensor::update();
    //I2cScanner::update();
    SlowSlaveI2c::update();
}

void Esp32DualCore::main()
{
    while(true)
    {
        /*
        QueueArray<uint8_t> dataToSend{};
        dataToSend.push(0);
        dataToSend.push(55);
        dataToSend.push(253);
        dataToSend.push(34);
        dataToSend.push(145);
        dataToSend.push(145);
        dataToSend.push(145);
        dataToSend.push(145);
        Serial.print("Sending ");
        Serial.print(dataToSend.count());
        Serial.println(" bytes...");

        SlowMasterI2c::send(0x66, dataToSend);

        delay(10);
        */
        
        QueueArray<uint8_t> dataReceived = SlowMasterI2c::request(76, 6);

        Serial.print("Master received ");
        Serial.print(dataReceived.count());
        Serial.println(" byte(s).");

        for(int i = 0; dataReceived.count() > 0; i++)
        {
            Serial.println(dataReceived.pop());
        }

        delay(5000);
        
    }
}

