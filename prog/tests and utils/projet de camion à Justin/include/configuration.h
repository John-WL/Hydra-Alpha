///////////////////////////////////////////////////////////////////////////////
//
// configuration.h
// 
// Created by: Justin Bourassa - TotalyNotAVirus
// Creation date: 12-11-2020
//
// Description: This header file is used configure all necessary settings of
//              the project in one file.
//
// Use case project: A20_VEHICLE
//
// Last modifications:
//
// 
///////////////////////////////////////////////////////////////////////////////



//// Hardware pinout configuration ////

#define RBCKLIGHT A0
#define RFRTLIGHT A5
#define LBCKLIGHT 21
#define LFRTLIGHT A10

#define BINSWITCH A2

#define PWM0 A1
#define PWM1 A7
#define PWM2 A6
#define PWM3 A9
#define PWM4 A8
#define PWM5 SCK

#define REDLED A12

#define V6BAT A3
#define V3BAT A13

//// Firmware Configuration ////

// Network Settings
#define Network_SSID       "etudiant7"
#define Network_Password   "etudiant7"
#define Network_Port        10024
#define Network_Identifier "ESP32_Truck"
#define Network_Target     "ESP32_Tour"
#define Network_Tower      "192.168.2.10"


#define Moving    'M'
#define Weight_Station 'W'
#define Sort_Station 'S'
#define Location3 'C'
#define Location4 'D'
