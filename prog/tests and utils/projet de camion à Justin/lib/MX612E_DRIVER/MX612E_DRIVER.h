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
Name:          MX612E_DRIVER.h
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to control TS1508S with PWMs
*/
#ifndef MX612E_DRIVER_h
#define MX612E_DRIVER_h

#define Forward   0
#define Backward  1


#include <Arduino.h>


class MX612E
{
    public:
        MX612E(int PWM0, int PWM5);
        void Motor(int Speed, int Direction);
    private:
        int _PWM0;
        int _PWM5;
};

#endif