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
#include "AUTOPILOT_SERVICE.h"

PCF8574 PCF_Driver(0x3A);                                      // PCF8574 library: Used for line tracer in AutoPilot Library
TS1508S Motor_Driver(PWM1, PWM2, PWM3, PWM4);                  // TS1508S Driver Library, used to control the motors of the vehicle
Driving Vehicle(Motor_Driver);                                 // Library used to drive and control the direction of the vehicle
Indicator Lights(RFRTLIGHT, LFRTLIGHT, RBCKLIGHT, LBCKLIGHT);  // Library used to drive the indicator lights of the vehicle

void Pilot_Start(void)
{
    PCF_Driver.begin();
    Vehicle.Stop();
    Lights.Change(ALL, OFF, STATIC);
    Lights.Execute();
}

int Pilot_Update(int Destination)
{
   static int Position;
   static int Direction = 0;
   static int OldLine;
   int Line = PCF_Driver.read8();
   switch (Line)
   {
   case 0xE4:
      Lights.Change(FRONT, ON, STATIC);
      Lights.Execute();
      if(Direction == 0)
      {Vehicle.GoForward(200);}
      else
      {Vehicle.GoBackward(200);}
      Position = Moving;
      break;

      case 0xE7:
      Lights.Change(FRONT, ON, STATIC);
      Lights.Execute();
      if(Direction == 0)
      {Vehicle.GoForward(200);}
      else
      {Vehicle.GoBackward(200);}
      Position = Moving;
      break;

      case 0xEE:
      Lights.Change(FRONT, ON, STATIC);
      Lights.Execute();
      if(Direction == 0)
      {Vehicle.GoForward(200);}
      else
      {Vehicle.GoBackward(200);}
      Position = Moving;
      break;

   case 0xE5:
      Lights.Change(RIGHT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

   case 0xE6:
      Lights.Change(RIGHT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

   case 0xE2:
      Lights.Change(RIGHT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

   case 0xE1:
      Lights.Change(RIGHT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

   case 0xEC:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoRight(200);
      Position = Moving;
      break;

   case 0xF0:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoRight(200);
      Position = Moving;
      break;

   case 0xE8:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoRight(200);
      Position = Moving;
      break;
   
   case 0xF6:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.Stop();
      Position = Weight_Station;
      break;

   case 0xF5:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.Stop();
      Position = Sort_Station;
      break;

   case 0xED:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      if(Destination == Weight_Station)
      {Vehicle.GoBackward(200);
       Direction = 1;}
      else
      {Vehicle.GoForward(200);
       Direction = 0;}
      Position = Moving;
      break;

   case 0xF4:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      if(Direction == 0)
      Vehicle.GoForward(200);
      else
      {Vehicle.GoBackward(200);}
      Position = Moving;
      break;

   case 0xFC:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

   case 0xF8:
      Lights.Change(LEFT, ON, BLINK);
      Lights.Execute();
      Vehicle.GoRight(200);
      Position = Moving;
      break;

      case 0xFF:
      Lights.Change(FRONT, ON, STATIC);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

      case 0xFE:
      Lights.Change(FRONT, ON, STATIC);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;

      case 0xE3:
      Lights.Change(FRONT, ON, STATIC);
      Lights.Execute();
      Vehicle.GoLeft(200);
      Position = Moving;
      break;
    

   default:
      Lights.Change(ALL, ON, BLINK);
      Lights.Execute();
      break;
   }

   if(Destination != Position)
   {
      if(Position != Moving)
      {
         if(Direction == 0)
         {Vehicle.GoForward(200);}
         else
         {Vehicle.GoBackward(200);}
      }
   }

   if(Destination == Sort_Station)
   {
      if(Position == Weight_Station)
      {
         Vehicle.GoForward(200);
      }
      Direction = 0;
   }
   return Position;
}