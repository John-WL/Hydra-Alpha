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
Name:          TS1508S_DRIVER.cpp
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to control TS1508S with PWMs
*/

#include <Arduino.h>
#include "TS1508S_DRIVER.h"

TS1508S::TS1508S(int PWM1, int PWM2, int PWM3, int PWM4)
{
    ledcAttachPin(PWM1, 1);
    ledcSetup(1, 12000, 8);
    _PWM1 = PWM1;
    ledcAttachPin(PWM2, 2);
    ledcSetup(2, 12000, 8);
    _PWM2 = PWM2;
    ledcAttachPin(PWM3, 3);
    ledcSetup(3, 12000, 8);
    _PWM3 = PWM3;
    ledcAttachPin(PWM4, 4);
    ledcSetup(4, 12000, 8);
    _PWM4 = PWM4;
}

void TS1508S::MotorA(int Speed, int Direction)
{
    if(Direction == Forward)
    {
        ledcWrite(1, 0);
        ledcWrite(2, Speed);
    }
    else if(Direction == Backward)
    {
        ledcWrite(1, Speed);
        ledcWrite(2, 0);
    }
    
}

void TS1508S::MotorB(int Speed, int Direction)
{
    if(Direction == Forward)
    {
        ledcWrite(3, 0);
        ledcWrite(4, Speed);
    }
    else if(Direction == Backward)
    {
        ledcWrite(3, Speed);
        ledcWrite(4, 0);
    }
}