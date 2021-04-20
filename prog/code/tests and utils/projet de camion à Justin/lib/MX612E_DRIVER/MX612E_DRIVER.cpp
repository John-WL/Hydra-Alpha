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
Name:          MX612_DRIVER.cpp
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to control TS1508S with PWMs
*/

#include <Arduino.h>
#include "MX612E_DRIVER.h"

MX612E::MX612E(int PWM0, int PWM5)
{
    ledcAttachPin(PWM0, 5);
    ledcSetup(5, 12000, 8);
    _PWM0 = PWM0;
    ledcAttachPin(PWM5, 6);
    ledcSetup(6, 12000, 8);
    _PWM5 = PWM5;
}

void MX612E::Motor(int Speed, int Direction)
{
    if(Direction == Forward)
    {
        ledcWrite(5, Speed);
        ledcWrite(6, 0);
    }
    else if(Direction == Backward)
    {
        ledcWrite(5, 0);
        ledcWrite(6, Speed);
    }
    
}
