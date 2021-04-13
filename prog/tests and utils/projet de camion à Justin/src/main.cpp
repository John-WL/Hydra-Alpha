/* 
                                                                  YAao,
                                                                   Y8888b,  
  _______    _        _         _   _       _                    ,oA8888888b,  
 |__   __|  | |      | |       | \ | |     | |             ,aaad8888888888888888bo,
    | | ___ | |_ __ _| |_   _  |  \| | ___ | |_         ,d888888888888888888888888888b,
    | |/ _ \| __/ _` | | | | | | . ` |/ _ \| __|      ,888888888888888888888888888888888b,
    | | (_) | || (_| | | |_| | | |\  | (_) | |_      d8888888888888888888888888888888888888,
    |_|\___/_\__\__,_|_|\__, | |_| \_|\___/ \__|    d888888888888888888888888888888888888888b
     /\     \ \    / (_) __/ |                     d888888P'                    `Y888888888888,
    /  \     \ \  / / _ |___/_   _ ___             88888P'                    Ybaaaa8888888888l
   / /\ \     \ \/ / | | '__| | | / __|           a8888'                      `Y8888P' `V888888
  / ____ \     \  /  | | |  | |_| \__ \         d8888888a                                `Y8888
 /_/    \_\     \/   |_|_|   \__,_|___/        AY/'' `\Y8b                                 ``Y8b
                                               Y'      `YP                                    ~~
                                                        `'                                       
Name:          main.cpp
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   This is the main file for the TSO S5 Project.
               This file brings togheter all the diffrent libaries
               to create the processes that controls the vehicle in
               the project. See the platformio.ini file for more
               technical information about this Firmware.
*/

#include "header.h" // Includes the header file that is used to include
                    // all libraries used in the Firmware.


/*
   Dual initial declerations.
   The following code declares all necessary functions
   for dual core use in the Firmware
*/
TaskHandle_t Task1;
TaskHandle_t Task2;
void WiFiHandle( void * pvParameters );
void VehicleHandle( void * pvParameters );


/* 
  Library declarations
  The following code declares and setup
  all nessecary classes in use for the firmware.
  If modification is nessecary per example:
  - The hardware has changed and new drivers are to be used
  - Different sevices or/and interfaces are to be used
  
  This part of the code is to be chaged. Just make sure of
  compatibility inside the libraries. See the library files
  for more information about it's functionnement.
*/


//// Function Callback Declarations /////
////   Time Based Service Setup     /////

Ticker TimerVehicle(Vehicle_Process, 10);
Ticker TimerCommunication(Communication_Process, 10);

/////////////////////////////////////////

void setup() {

  /* !!!!IMPORTANT - DO NOT REMOVE THE FOLLOWING CODE!!!!
     
     The  two  lines of  following  code removes the Watchdog timers 
     of  both  cores  in the ESP32. This prevents involontary Kernel
     panics  which  causes  the  system  to reboot. While doing this
     prevents FreeRTOS from rebooting if the codes cause stagnation.
     The Pros of doing this are bigger than this con. The use of the
     Ticker  library causes a lot of Kernel panics inside the OS due
     to it's nature. This leads to the removal of the timers.
  */
  disableCore0WDT(); // Do not remove those two lines
  disableCore1WDT(); // See text above


  // Global Setup function.
  // Setup code wich is used by both cores

  Serial.begin(115200); // Starts the serial port with a baud rate of 115200

  // End of Global Setup Function


  // Dual Core Setup.
  // This code creates a task in the two ESP32 Cores
  xTaskCreatePinnedToCore(
    WiFiHandle,           // Function that will be executed in this core
    "Task1",              // Task name of the core
    10000,                // Stack size of the core
    NULL,                 // Task input parameter
    1,                    // Priority of the task
    &Task1,               // Task Handle
    0);                   // Core selected for the task
    delay(500);

  xTaskCreatePinnedToCore(
    VehicleHandle,        // Function that will be executed in this core
    "Task2",              // Task name of the core
    10000,                // Stack size of the core
    NULL,                 // Task input parameter
    1,                    // Priority of the task
    &Task2,               // Task Handle
    1);                   // Core selected for the task
    delay(500);
    // End of Dual Core Setup
}



void WiFiHandle(void * pvParameters)
{
  // Start of Core 0 Setup
  Communication_Init();
  TimerCommunication.start();
  // End of Core 0 Setup


  for(;;)
  {
    // Start of Core 0 Loop
    TimerCommunication.update();
    // End of Core 0 Loop
  }
}



void VehicleHandle(void * pvParameters)
{
  // Start of Core 1 Setup
  Vehicle_Init();
  TimerVehicle.start();
  // End of Core 1 Setup


  for(;;)
  {
    // Start of Core 1 Loop
    TimerVehicle.update();
    // End of Core 1 Loop
  }
}





void loop() {  // The Loop function is existing but not used due to dual core implementation
}              // The removal of the loop function is not possible due to the nature of the
               // Arduino framework used for this Frimware

