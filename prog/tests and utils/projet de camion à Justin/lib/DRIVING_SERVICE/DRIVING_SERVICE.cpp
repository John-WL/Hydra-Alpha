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
Name:          DRIVING_SERVICE.cpp
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to Drive the vehicle
*/

#include <Arduino.h>
#include "DRIVING_SERVICE.h" 

Driving::Driving(TS1508S Driver)
{
   _Driver = &Driver;
   _Driver->MotorA(0, Forward);
   _Driver->MotorB(0, Forward);
}

void Driving::GoForward(int Speed)
{
   _Driver->MotorA(Speed, Forward);
   _Driver->MotorB(Speed, Forward);
}

void Driving::GoBackward(int Speed)
{
   _Driver->MotorA(Speed, Backward);
   _Driver->MotorB(Speed, Backward);
}

void Driving::GoLeft(int Speed)
{
   _Driver->MotorA(Speed, Backward);
   _Driver->MotorB(Speed, Forward);
}

void Driving::GoRight(int Speed)
{
   _Driver->MotorA(Speed, Forward);
   _Driver->MotorB(Speed, Backward);
}

void Driving::Stop(void)
{
   _Driver->MotorA(0, Forward);
   _Driver->MotorB(0, Forward);
}