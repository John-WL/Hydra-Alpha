//
//                YOU MUST DEFINE GLOBALLY :
//                     (dans main.c)
//
//                struct CANInfo BufferCAN;
//
//*************************************************************//
//
// Structure principale = BufferCAN
//
// Camion = .truck
// Centre de tri = .tri
// Poste de controle = .commande
// Centre de pese = .pese
//
// Utiliser les .all pour loader et unloader des buffers
// Utiliser les .split pour ecrire ou lire l'information
// Le prefixe FE_ donne acces au flag d'erreurs pour le module.
//  (pas de flag pour le poste de controle)
//
// Informations accessibles:
//
// Poste de controle : .state
//                     .unit
//
// Centre de tri     : .state
//                     .type
//                     .loaded
//
// Camion            : .state
//                     .benne
//                     .position
//
// Centre de pese    : .state
//                     .unit
//                     .WeightMSB
//                     .WeightLSB
//
// Flag d'erreurs    : .errorN (N = 1-8)
// 
//*************************************************************//
//
// Exemples:
// 
// BufferCAN.commande.split.state = OFF;
//
// SBUF0 = BufferCAN.commande.all;
//
// int value = BufferCAN.pese.ctrl.split.WeightMSB<<8;
// value += BufferCAN.pese.WeightLSB;
// value <<= 2;
//
// BufferCAN.tri.split.type = ORANGE;
//
// BufferCAN.FE_truck.split.error1 = ON;
//
//*************************************************************//

#ifndef SERVICECANH
 #define SERVICECANH
 
#define KG 		0
#define LBS 	1
#define LEVE 	1
#define BAISSE  0
#define UNKNOWN 0
#define ORANGE  1
#define METAL   2
#define NOIR    3
#define CHARGE  1
#define VIDE    0
#define CENTRE_TRI   0
#define CENTRE_PESE 32
                       
                                       // Poste de controle
struct SCtrl
{ 
	unsigned char reset_pese : 1;
	unsigned char reset_truck : 1;
	unsigned char reset_tri : 1;
	unsigned char reset_launch : 1;
	unsigned char unit : 1;
	unsigned char nullbit : 2;
	unsigned char state : 1;	
};

                                           // Flag d'erreur
struct SFlag
{
	unsigned char error8 : 1;
	unsigned char error7 : 1;
	unsigned char error6 : 1;
	unsigned char error5 : 1;
	unsigned char error4 : 1;
	unsigned char error3 : 1;
	unsigned char error2 : 1;
	unsigned char error1 : 1;	
};

                                           // Centre de tri
struct STri
{
	unsigned char nullbit 	: 4;
	unsigned char loaded 	: 1;
	unsigned char type 	    : 2;
	unsigned char state 	: 1;
};

                                                  // Camion
struct STruck
{
	unsigned char position 	: 6;
	unsigned char benne	: 1;
	unsigned char state 	: 1;		
};

                                          // Centre de pese
struct SPeseCtrl
{
	unsigned char WeightMSB	: 6;
	unsigned char unit	: 1;
	unsigned char state 	: 1;		
};

union UCtrl
{
	struct SCtrl split;
	unsigned char all;
};

union UFlag
{
	struct SFlag split;
	unsigned char all;
};

union UTri
{
	struct STri split;
	unsigned char all;
};

union UTruck
{
	struct STruck split;
	unsigned char all;
};

union UPeseCtrl
{
	struct SPeseCtrl split;
	unsigned char all;
};

struct SPese
{
	union UPeseCtrl ctrl;
	unsigned char WeightLSB;
};
                                              // Principale
struct CANInfo
{
	union UCtrl commande;
	union UTri tri;
	union UFlag FE_tri;
	union UTruck truck;
	union UFlag FE_truck;
	struct SPese pese;	
	union UFlag FE_pese;
};

extern struct CANInfo BufferCAN;

#endif