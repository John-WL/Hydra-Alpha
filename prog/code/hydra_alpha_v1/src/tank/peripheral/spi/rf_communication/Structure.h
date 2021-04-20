#ifndef STRUCTUREH
	#define STRUCTUREH
	
// Définitions des structures d'entrée et sortie de la class HydraRF.
//
// Lors de l'envoie d'une trame de communication, le data des structures sera précédé de GO et suivit d'un checksum sur 1 byte.
//
// Unités: distance/distanceSonar = cm    -    sigStrength = %    -    batteryLevel/spareBat/mainBat = %
//
// Pour les exemples nous assumerons que la class a été déclaré comme suit: HydraRF hydraRF (4,5);
//
// Adresse mémoire haute et MSB sur la gauche, adresse mémoire basse et LSB syur la droite.
//
//
// Information en provenance de la remote:
//
// Structure principale : ComRemote - 8 bytes
//
//  |                           |                                 |
//           4 bytes                       4 bytes
//            omega                         alpha

struct sCom
{
	struct sTank alpha;
	struct sTank omega;
};

// Structures secondaires : alpha et omega - 4 bytes
//
//  |           |           |            |           |
//     1 byte      1 byte      1 byte       1 byte
//     distance    camera      moteur        mode
//
// Ex. lecture: unsigned char var = hydraRF.ComRemote.alpha.mode;
//              unsigned char var = hydraRF.ComRemote.alpha.distance;
//              unsigned char var = hydraRF.ComRemote.omega.mode;
//              unsigned char var = hydraRF.ComRemote.omega.distance;
//
// Ex. écriture: hydraRF.ComRemote.alpha.mode = ALPHA_TO_REMOTE_SWARM_MODE;
//				 hydraRF.ComRemote.alpha.distance = SERVO_RIGHT;
//				 hydraRF.ComRemote.omega.mode = AUTO;
//				 hydraRF.ComRemote.omega.distance = SERVO_LEFT;

struct sTank
{
	unsigned char mode;
	union uMoteur moteur;
	union uCam	  camera;
	unsigned char distance;
};

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
// Ex. écriture: hydraRF.ComRemote.alpha.moteur.bit.left = TRUE;
//               hydraRF.ComRemote.alpha.moteur.bit.up = TRUE;
//               hydraRF.ComRemote.alpha.moteur.bit.down = TRUE;
//               hydraRF.ComRemote.alpha.moteur.bit.right = TRUE;
//               hydraRF.ComRemote.alpha.moteur.bit.speed = 5;
//               hydraRF.ComRemote.omega.moteur.bit.left = TRUE;
//               hydraRF.ComRemote.omega.moteur.bit.up = TRUE;
//               hydraRF.ComRemote.omega.moteur.bit.down = TRUE;
//               hydraRF.ComRemote.omega.moteur.bit.right = TRUE;
//               hydraRF.ComRemote.omega.moteur.bit.speed = 5;
//
// Ex. lecture:  unsigned char var = hydraRF.ComRemote.alpha.moteur.split.direction;
//               unsigned char var = hydraRF.ComRemote.alpha.moteur.split.speed;
//               unsigned char var = hydraRF.ComRemote.omega.moteur.split.direction;
//               unsigned char var = hydraRF.ComRemote.omega.moteur.split.speed;

union uMoteur
{
	struct sMoteurS bit;
	struct sMoteurM split;
	unsigned char full;
};

struct sMoteurM
{
	unsigned char speed: 	 4;
	unsigned char direction: 4;
};

struct sMoteurS
{
	unsigned char speed: 4;
	unsigned char right: 1;
	unsigned char down:  1;
	unsigned char up:    1;
	unsigned char left:	 1;
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
// Ex. écriture: hydraRF.ComRemote.alpha.camera.split.tilt = SERVO_UP;
//               hydraRF.ComRemote.alpha.camera.split.rotation = SERVO_RIGHT;
//               hydraRF.ComRemote.omega.camera.split.tilt = SERVO_DOWN;
//               hydraRF.ComRemote.omega.camera.split.rotation = SERVO_LEFT;
//
// Ex. lecture: if(hydraRF.ComRemote.alpha.camera.split.tilt == SERVO_UP)
//              if(hydraRF.ComRemote.alpha.camera.split.rotation == SERVO_RIGHT)
//              if(hydraRF.ComRemote.omega.camera.split.tilt == SERVO_DOWN)
//              if(hydraRF.ComRemote.omega.camera.split.rotation == SERVO_LEFT)

union uCam
{
	struct sCam split;
	unsigned char full;
};

struct sCam
{
	unsigned char rotation: 2;
	unsigned char tilt:		2;
	unsigned char null:		4;
};


// Inforamtion en provenance d'Alpha:
//
// Structure principale: TrameAlpha - 5 bytes
//
//  |       |       |             |        |
//   1 byte  1 byte     2 bytes     1 byte
//    error   mode   distanceSonar batteryLevel
//
// Ex. lecture: unsigned char var = hydraRF.TrameAlpha.error;
//              unsigned char var = hydraRF.TrameAlpha.mode;
//              unsigned char var = hydraRF.TrameAlpha.batteryLevel;
//
// Ex. écriture: hydraRF.TrameAlpha.error = 0x56;
//               hydraRF.TrameAlpha.mode = ALPHA_TO_REMOTE_LISTENING_TO_COMMANDS_MODE;
//				 hydraRF.TrameAlpha.batteryLevel = 70;

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
// Ex. lecture: unsigned char var = hydraRF.ComOmega.error;
//              unsigned char var = hydraRF.ComOmega.sigStrength;
//              unsigned char var = hydraRF.ComOmega.mode;
//              unsigned char var = hydraRF.ComOmega.spareBat;
//              unsigned char var = hydraRF.ComOmega.mainBat;
//
// Ex. écriture: hydraRF.ComOmega.error = 0x56;
//               hydraRF.ComOmega.sigStrength = 99;
//               hydraRF.ComOmega.mode = AUTO;
//				 hydraRF.ComOmega.spareBat = 70;
//				 hydraRF.ComOmega.mainBat = 90;

struct sComOmega
{
	unsigned char mainBat;
	unsigned char spareBat;
	unsigned char mode;
	union uDistance distance;
	unsigned char sigStrength;
	unsigned char error;
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
// Ex. écriture: hydraRF.TrameAlpha.distanceSonar.full = 0x0234;
//               hydraRF.ComOmega.distance.full = 0x0234;
//
// Ex. lecture: unsigned int = hydraRF.TrameAlpha.distanceSonar.full;
//              unsigned int = hydraRF.ComOmega.distance.full;


struct sDistance
{
	unsigned int lsb: 8;
	unsigned int msb: 8;
};

union uDistance
{
	struct sDistance split;
	unsigned int full;
};


#ifndef ALPHA_TO_REMOTE_LISTENING_TO_COMMANDS_MODE
	#define ALPHA_TO_REMOTE_LISTENING_TO_COMMANDS_MODE 0
#endif

#ifndef ALPHA_TO_REMOTE_SWARM_MODE
	#define ALPHA_TO_REMOTE_SWARM_MODE 1
#endif

#define SERVO_LEFT			1
#define SERVO_RIGHT			2

#define SERVO_UP			1
#define SERVO_DOWN			2

#ifndef TRUE
	#define TRUE 			1
#endif

#ifndef FALSE
	#define FALSE 			0
#endif

#endif