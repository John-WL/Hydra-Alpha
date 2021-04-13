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
Name:          INDICATOR_SERVICE.cpp
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to control indicator lights
*/

#include <Arduino.h>
#include "INDICATOR_SERVICE.h"

Indicator::Indicator(int FrtR, int FrtL, int BckR, int BckL)
{
    pinMode(FrtR, OUTPUT);
    _FrtR = FrtR;
    pinMode(FrtL, OUTPUT);
    _FrtL = FrtL;
    pinMode(BckR, OUTPUT);
    _BckR = BckR;
    pinMode(BckL, OUTPUT);
    _BckL = BckL;
} 

void Indicator::Execute(void)
{
    switch (_Lights)
    {
    case FRONT:
        if(_Mode == STATIC)
        {
            digitalWrite(_FrtL, _Set);
            digitalWrite(_FrtR, _Set);
        }
        else if(_Mode == BLINK)
        {
            digitalWrite(_FrtL, !digitalRead(_FrtL));
            digitalWrite(_FrtR, !digitalRead(_FrtR));
        }
        break;

    case BACK:
        if(_Mode == STATIC)
        {
            digitalWrite(_BckL, _Set);
            digitalWrite(_BckR, _Set);
        }
        else if(_Mode == BLINK)
        {
            digitalWrite(_BckL, !digitalRead(_BckL));
            digitalWrite(_BckR, !digitalRead(_BckR));
        }
        break;

    case LEFT:
        if(_Mode == STATIC)
        {
            digitalWrite(_FrtL, _Set);
            digitalWrite(_BckL, _Set);
        }
        else if(_Mode == BLINK)
        {
            digitalWrite(_FrtL, !digitalRead(_FrtL));
            digitalWrite(_BckL, !digitalRead(_BckL));
        }
        break;

    case RIGHT:
        if(_Mode == STATIC)
        {
            digitalWrite(_FrtR, _Set);
            digitalWrite(_BckR, _Set);
        }
        else if(_Mode == BLINK)
        {
            digitalWrite(_FrtR, !digitalRead(_FrtR));
            digitalWrite(_BckR, !digitalRead(_BckR));
        }
        break;

    case ALL:
        if(_Mode == STATIC)
        {
            digitalWrite(_FrtL, _Set);
            digitalWrite(_FrtR, _Set);
            digitalWrite(_BckL, _Set);
            digitalWrite(_BckR, _Set);
        }
        else if(_Mode == BLINK)
        {
            digitalWrite(_FrtL, !digitalRead(_FrtL));
            digitalWrite(_FrtR, !digitalRead(_FrtR));
            digitalWrite(_BckL, !digitalRead(_BckL));
            digitalWrite(_BckR, !digitalRead(_BckR));
        }
        break;
    
    default:
        break;
    }
}

void Indicator::Change(int Lights, int Set, int Mode)
{
    _Lights = Lights;
    _Set = Set;
    _Mode = Mode;
}

