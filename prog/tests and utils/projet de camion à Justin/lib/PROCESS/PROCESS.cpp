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

#include "PROCESS.h"

char* TargetAddress;
const char* ssid     =      Network_SSID;
const char* password =      Network_Password;
unsigned int localUdpPort = Network_Port;

static char  receptionMessage[2];
static char* reception = receptionMessage;
static char  OldreceptionMessage[2];
static char* Oldreception = OldreceptionMessage;

static unsigned char  SendMessage[1];
static unsigned char* Sender = SendMessage;
int sent = 0;
int StartFlag;

static char  EmptyMessage[2] = {0xFF, 0xFF};
static char* Empty = EmptyMessage;

struct CANInfo BufferCAN;
struct Global_Data Data;

int FirstStep;

/* 
  Library declarations
  The following code declares and setup
  all nessecary classes in use for the firmware.
  If modification is nessecary per example:
  - The hardware has changed and new drivers are to be used
  - Different sevices or/and interfaces are to be used
  
  This part of the code is to be chaged. Just make sure of
  compatibility inside the libraries. See the library files
  for more information about it's functionnement.
*/
TS1508S Motor_Driver2(PWM1, PWM2, PWM3, PWM4);                  // TS1508S Driver Library, used to control the motors of the vehicle
Driving Vehicle2(Motor_Driver2);  

MX612E BIN_Driver(PWM0, PWM5);
BIN_SERVICE Bin1(BIN_Driver, BINSWITCH);

UDP_COMMUNICATION UDP_COM(ssid, password, localUdpPort);       // Library used to communicate with other devices on a network with UDP
IPAddress targetIP;


void Vehicle_Init(void)
{
   Data.Destination = Sort_Station;
   BufferCAN.tri.split.type   = 0;
   BufferCAN.tri.split.loaded = 0;
   Pilot_Start();
   pinMode(BINSWITCH, INPUT);
   StartFlag = 0;
}

void Vehicle_Process(void)
{
   if(Data.Bin_State == 1)
   {
      if(Bin1.Activate() == 1)
      {
         Data.Bin_State = 0;
         BufferCAN.truck.split.benne = 1;
      }
   }
   else if (Data.Bin_State == 0)
   {
      Data.Location = Pilot_Update(Data.Destination);
      BufferCAN.truck.split.benne = 0;
   }

   if(Data.Destination == Weight_Station)
   {
      if(Data.Location == Moving)
      {
         BufferCAN.truck.split.position = 3;
      }
      else if(Data.Location == Weight_Station)
      {
         BufferCAN.truck.split.position = 1;
      }
      
   }

   if(Data.Destination == Sort_Station)
   {
      if(Data.Location == Moving)
      {
         BufferCAN.truck.split.position = 4;
      }
      else if(Data.Location == Sort_Station)
      {
         BufferCAN.truck.split.position = 2;
      }
      
   }
}

void Communication_Init(void)
{
   UDP_COM.ConnectToWiFi();
   MDNS.begin(Network_Identifier);
   Serial.print("Getting Target's IP");
   for (size_t i = 0; i <= 10; i++)
   {
      Serial.print(".");
      delay(1000);
   }
   targetIP = MDNS.queryHost(Network_Target);
   //targetIP.fromString(Network_Tower);
   Serial.println(targetIP);
   BufferCAN.commande.split.state = 0;
   

}

void Communication_Process(void)
{
   reception = UDP_COM.ReceivePacket();

   if(strcmp(reception, Empty) != 0)
   {
   //if(strcmp(reception, Oldreception) != 0)
   //{
      BufferCAN.commande.all = reception[0];
      BufferCAN.tri.all = reception[1];

      Serial.printf("%02X %02X\n", BufferCAN.commande.all, BufferCAN.tri.all);

      SendMessage[0] = BufferCAN.truck.all;
      Serial.printf("%02X\n", BufferCAN.truck.all);

   if(BufferCAN.commande.split.state == 1)
   {
      if(StartFlag == 0)
      {
       Data.Destination = Weight_Station;
       StartFlag = 1;
       BufferCAN.truck.split.state = 1;
      }
   }

   if((BufferCAN.tri.split.type == 1) || (BufferCAN.tri.split.type == 2) )
   {
      if(BufferCAN.tri.split.loaded == 0)
      {
        Data.Destination = Sort_Station;
      }
   }
   

   if(Data.Location == Sort_Station)
   {
      if(BufferCAN.tri.split.loaded == 1)
      {
         Data.Destination = Weight_Station;
      }
   }

   if(Data.Location == Weight_Station)
   {
      if(BufferCAN.tri.split.loaded == 1)
      {
        if(BufferCAN.tri.split.type == 1)
        {
           Data.Bin_State = 1;
        }
      }
   }

      Serial.println(Data.Destination);

      UDP_COM.SendPacket(Sender, targetIP);
      Serial.println("Reply Sent!");
      strcpy(Oldreception, reception);
   //}
   }
}