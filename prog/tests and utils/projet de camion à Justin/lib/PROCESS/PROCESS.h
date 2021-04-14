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
Name:          INDICATOR_SERVICE.h
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to control indicator lights
*/
#ifndef PROCESS_h
#define PROCESS_h

#include "../../include/configuration.h"
#include "../../include/serviceCAN.h"
#include <Arduino.h>
#include "AUTOPILOT_SERVICE.h"
#include "BIN_SERVICE.h"
#include "UDP_COMMUNICATION.h"
#include <ESPmDNS.h>

struct Global_Data
{
    char Location;
    char Destination;
    int GoToNext;
    int Bin_State;

};


void Vehicle_Init(void);
void Vehicle_Process(void);
void Communication_Init(void);
void Communication_Process(void);

#endif