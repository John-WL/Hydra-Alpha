///////////////////////////////////////////////////////////////////////////////
//
// header.h
// 
// Created by: Justin Bourassa - TotalyNotAVirus
// Creation date: 12-11-2020
//
// Description: This header file is used to merge all necessary includes in one
//              document as to avoid copy-pasting which can be error prone.
//
// Use case project: A20_VEHICLE
//
// Last modifications:
//
// 
///////////////////////////////////////////////////////////////////////////////

#include <Arduino.h> // Necessary for arduino style progamming

#include "configuration.h"  // Loads Hardware configuration file

//// Driver Include ////

#include <Wire.h>     // Adds I2C functions

#include <WiFi.h>     // Adds basic WiFi functions
#include <WiFiUdp.h>  // Adds WiFi UDP communication functions

#include <Ticker.h>   // Enables Non-blocking repeateble function callback

#include "PCF8574.h"

#include "INDICATOR_SERVICE.h"

#include "TS1508S_DRIVER.h"

#include "DRIVING_SERVICE.h"

#include "MX612E_DRIVER.h"

#include "AUTOPILOT_SERVICE.h"

#include "UDP_COMMUNICATION.h"

#include "BIN_SERVICE.h"

#include "PROCESS.h"

#include "serviceCAN.h"

