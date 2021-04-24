#ifndef STRUCTUREH
	#define STRUCTUREH

  // John-W added:
#include "Arduino.h"

// Définitions des structures d'entrée et sortie de la communication RF.
//
// Lors de l'envoie d'une trame de communication, le data des structures sera précédé de GO et suivit d'un checksum sur 1 byte.
//
// Unités: distance/distanceSonar = cm    -    sigStrength = %    -    batteryLevel/spareBat/mainBat = %
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

// Structures bitwise : camera - 1 byte
//   |                                |
//               1 byte
//                full
//
//                split
//   |              |        |        |
//       4 bits       2 bits   2 bits
//        null         tilt   rotation
//
// Ex. écriture: ComRemote.alpha.camera.split.tilt = SERVO_UP;
//               ComRemote.alpha.camera.split.rotation = SERVO_RIGHT;
//               ComRemote.omega.camera.split.tilt = SERVO_DOWN;
//               ComRemote.omega.camera.split.rotation = SERVO_LEFT;
//
// Ex. lecture: if(ComRemote.alpha.camera.split.tilt == SERVO_UP)
//              if(ComRemote.alpha.camera.split.rotation == SERVO_RIGHT)
//              if(ComRemote.omega.camera.split.tilt == SERVO_DOWN)
//              if(ComRemote.omega.camera.split.rotation == SERVO_LEFT)

struct sCam
{
  unsigned char rotation: 2;
  unsigned char tilt:   2;
  unsigned char null:   4;
};

union uCam
{
  struct sCam split;
  unsigned char full;
};

// Structures secondaires : alpha et omega - 4 bytes
//
//  |           |           |            |           |
//     1 byte      1 byte      1 byte       1 byte
//     distance    camera      moteur        mode
//
// Ex. lecture: unsigned char var = ComRemote.alpha.mode;
//              unsigned char var = ComRemote.alpha.distance;
//              unsigned char var = ComRemote.omega.mode;
//              unsigned char var = ComRemote.omega.distance;
//
// Ex. écriture: ComRemote.alpha.mode = ALPHA_TO_REMOTE_SWARM_MODE;
//         ComRemote.alpha.distance = SERVO_RIGHT;
//         ComRemote.omega.mode = AUTO;
//         ComRemote.omega.distance = SERVO_LEFT;

struct sTank
{
  unsigned char mode;
  union uMoteur moteur;
  union uCam    camera;
  unsigned char distance;
};

// Structure principale : ComRemote - 8 bytes
//
//  |                           |                                 |
//           4 bytes                       4 bytes
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
  uint16_t lsb: 8;
  uint16_t msb: 8;
};

union uDistance
{
  struct sDistance split;
  uint16_t full;
};


// Inforamtion en provenance d'Alpha:
//
// Structure principale: TrameAlpha - 5 bytes
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
} AlphaToRemoteCommunicationFormat;

// Inforamtion en provenance d'Omega:
//
// Structure principale: ComOmega - 7 bytes
//
//  |       |       |             |        |        |        | 
//   1 byte  1 byte     2 bytes     1 byte   1 byte   1 byte
//    error sigStrength  distance    mode    spareBat mainBat
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
//				 ComOmega.spareBat = 70;
//				 ComOmega.mainBat = 90;

struct sComOmega
{
	unsigned char mainBat;
	unsigned char spareBat;
	unsigned char mode;
	union uDistance distance;
	unsigned char sigStrength;
	unsigned char error;
};

#endif
