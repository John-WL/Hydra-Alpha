#ifndef STRUCTUREH
	#define STRUCTUREH

#include "Arduino.h"
#define ALPHA

// Définitions des structures d'entrée et sortie de la communication RF.
//
// Lors de l'envoie d'une trame de communication, le data des structures sera précédé de GO et suivit d'un checksum sur 1 byte.
//
// Unités: distance/distanceSonar = cm    -    sigStrength/sigWifi = %    -    batteryLevel/spareBat/mainBat = %
//
// Adresse mémoire haute et MSB sur la gauche, adresse mémoire basse et LSB sur la droite.
//
// Information en provenance de la remote:
//
// Structures bitwise : moteur - 1 byte
//
//  |                                     |
//                1 byte
//                 full
//
//                split
//  |                |                    |
//       4 bits             4 bits
//       direction          speed
//
//                 bit
//  |   |    |    |    |                    |
//   1b   1b   1b   1b         4bits
//  left  up  down right       speed
//
// Ex. écriture: ComRemote.alpha.moteur.bit.left = TRUE;
//               ComRemote.alpha.moteur.bit.up = TRUE;
//               ComRemote.alpha.moteur.bit.down = TRUE;
//               ComRemote.alpha.moteur.bit.right = TRUE;
//               ComRemote.alpha.moteur.bit.speed = 5;
//               ComRemote.omega.moteur.bit.left = TRUE;
//               ComRemote.omega.moteur.bit.up = TRUE;
//               ComRemote.omega.moteur.bit.down = TRUE;
//               ComRemote.omega.moteur.bit.right = TRUE;
//               ComRemote.omega.moteur.bit.speed = 5;
//
// Ex. lecture:  unsigned char var = ComRemote.alpha.moteur.split.direction;
//               unsigned char var = ComRemote.alpha.moteur.split.speed;
//               unsigned char var = ComRemote.omega.moteur.split.direction;
//               unsigned char var = ComRemote.omega.moteur.split.speed;

struct sMoteurM
{
  unsigned char speed:   4;
  unsigned char direction: 4;
};

struct sMoteurS
{
  unsigned char speed: 4;
  unsigned char right: 1;
  unsigned char down:  1;
  unsigned char up:    1;
  unsigned char left:  1;
};

union uMoteur
{
  struct sMoteurS bit;
  struct sMoteurM split;
  unsigned char full;
};

// Structures bitwise : servo - 1 byte
//   |                                |
//               1 byte
//                full
//
//                split
//   |       |       |        |        |
//    2 bits   2bits   2 bits   2 bits
//      null  distance  tilt   rotation
//
// Ex. écriture: ComRemote.alpha.servo.split.tilt = SERVO_UP;
//               ComRemote.alpha.servo.split.rotation = SERVO_RIGHT;
//               ComRemote.omega.servo.split.tilt = SERVO_DOWN;
//               ComRemote.omega.servo.split.rotation = SERVO_LEFT;
//
// Ex. lecture: if(ComRemote.alpha.servo.split.tilt == SERVO_UP)
//              if(ComRemote.alpha.servo.split.rotation == SERVO_RIGHT)
//              if(ComRemote.omega.servo.split.tilt == SERVO_DOWN)
//              if(ComRemote.omega.servo.split.rotation == SERVO_LEFT)

struct sServo
{
  unsigned char rotation: 2;
  unsigned char tilt:     2;
  unsigned char distance: 2;
  unsigned char null:     2;
};

union uServo
{
  struct sServo split;
  unsigned char full;
};

// Structures secondaires : alpha et omega - 3 bytes
//
//    |           |            |           |
//        1 byte      1 byte       1 byte
//         servo      moteur        mode
//
// Ex. lecture: unsigned char var = ComRemote.alpha.mode;
//              unsigned char var = ComRemote.omega.mode;
//
// Ex. écriture: ComRemote.alpha.mode = ALPHA_TO_REMOTE_SWARM_MODE;
//         ComRemote.omega.mode = AUTO;

struct sTank
{
  unsigned char mode;
  union uMoteur moteur;
  union uServo servo;
};

// Structure principale : ComRemote - 6 bytes
//
//  |                           |                                 |
//           3 bytes                       3 bytes
//            omega                         alpha

struct sCom
{
	sTank alpha;
	sTank omega;
};

// Structure bitwise: distanceSonar / distance - 2 bytes
//
//  |                                      |
//                 2 bytes
//                  full
//
//                  split
//  |                  |                   |
//       1 byte              1 byte
//        MSB                 LSB
//
// Ex. écriture: TrameAlpha.distanceSonar.full = 0x0234;
//               ComOmega.distance.full = 0x0234;
//
// Ex. lecture: unsigned int = TrameAlpha.distanceSonar.full;
//              unsigned int = ComOmega.distance.full;


struct sDistance
{
  unsigned char lsb;
  unsigned char msb;
};

union uDistance
{
  struct sDistance split;
  uint16_t full;
};


// Inforamtion en provenance d'Alpha:
//
// Structure principale: TrameAlpha - 6 bytes
//
//  |       |       |             |        |
//   1 byte  1 byte     2 bytes     1 byte
//    error   mode   distanceSonar batteryLevel
//
// Ex. lecture: unsigned char var = TrameAlpha.error;
//              unsigned char var = TrameAlpha.mode;
//              unsigned char var = TrameAlpha.batteryLevel;
//
// Ex. écriture: TrameAlpha.error = 0x56;
//               TrameAlpha.mode = ALPHA_TO_REMOTE_LISTENING_TO_COMMANDS_MODE;
//				       TrameAlpha.batteryLevel = 70;

typedef struct
{
    unsigned char batteryLevel;
    union uDistance distanceSonar;
    unsigned char mode;
	  unsigned char error;
    unsigned char sigWifi;
} AlphaToRemoteCommunicationFormat;

// Inforamtion en provenance d'Omega:
//
// Structure principale: ComOmega - 8 bytes
//
//  |       |          |         |           |         |        |        | 
//   1 byte   1 byte     1 byte     2 bytes     1 byte   1 byte   1 byte
//    error   sigWifi  sigStrength  distance    mode    spareBat  mainBat
//
// Ex. lecture: unsigned char var = ComOmega.error;
//              unsigned char var = ComOmega.sigStrength;
//              unsigned char var = ComOmega.mode;
//              unsigned char var = ComOmega.spareBat;
//              unsigned char var = ComOmega.mainBat;
//
// Ex. écriture: ComOmega.error = 0x56;
//               ComOmega.sigStrength = 99;
//               ComOmega.mode = AUTO;
//				       ComOmega.spareBat = 70;
//				       ComOmega.mainBat = 90;

struct sComOmega
{
	unsigned char mainBat;
	unsigned char spareBat;
	unsigned char mode;
	union uDistance distance;
	unsigned char sigStrength;
  unsigned char sigWifi;
	unsigned char error;
};

#endif
