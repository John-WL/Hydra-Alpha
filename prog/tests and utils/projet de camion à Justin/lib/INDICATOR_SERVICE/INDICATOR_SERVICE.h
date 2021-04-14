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
#ifndef INDICATOR_SERVICE_h
#define INDICATOR_SERVICE_h

// Library defines

#define STATIC 0
#define BLINK  1

#define FRONT  0
#define BACK   1
#define LEFT   2
#define RIGHT  3
#define ALL    4

#define OFF    0
#define ON     1

#include <Arduino.h>


class Indicator
{
    public:
        Indicator(int FrtR, int FrtL, int BckR, int BckL);
        void Execute(void);
        void Change(int Lights, int Set, int Mode);
        
    private:
        int _FrtR;
        int _FrtL;
        int _BckR;
        int _BckL;
        int _Lights;
        int _Set;
        int _Mode;
};

#endif