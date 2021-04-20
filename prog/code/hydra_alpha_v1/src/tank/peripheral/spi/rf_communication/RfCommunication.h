/*

#ifndef HYDRARFH
 #define HYDRARFH

// Class HydraRF
//
// Implimentation d'un protocole de communication entre 3 module nRF24L01+.
//                                               (Remote, Alpha, Omega)
//
// Driver : SPI.h, RF24.h
// Interface: RF24Network.h 
// Process: HydraRF.h
// Service: Structure.h 
//
// At least one must be define in main.h
//
// #define REMOTE
// #define ALPHA
// #define OMEGA
//
// La class offre des communications automatisées avec des méchanismes de re-connection 
// en cas d'échec ainsi qu'une sauvegarde d'arrêt de mouvement automatique. 
//
// L'utilisation d'une structure nodale permet le déplacement d'un node d'un niveau 
// à l'autre afin d'atteindre notre objectif d'étendre la porté du notre communication RF.
//
// Une communication abrégée s'oppère entre les deux tanks lorsque l'un deux essaie de se connecter à
// une nouveau node. Lorsque qu'un tank essaie de se connecter sur l'autre tank (level = LVL2), la posibilité
// de changer de node est impossible pour le deuxième tank (lock = LOCKED).
//
// ***************************************** IMPORTANT ***************************************************
//
// Si un tank devait tomber Out-of-Bound de la remote alors que lock = LOCKED 
// (deuxième tank déja Out-of-Bound de la remote), la seule façon de récupérer la communication
// est remettre le tank In-Bound. La récuperation via l'autre node est impossible.
//
// Si les deux tanks devaient devenir Out-of-Bound de la remote en même temps, cela pourrait
// produire une erreur de communication irrécupérable (les deux tanks LOCKED au level = LVL2).
// 
//********************************************************************************************************
//
// L'information (entrée et sortie) passe par l'utilisation de trois structures (voir Structure.h).
//

#include "main.h"
#include "Structure.h"

#define COM_REMOTE_LEN		11
#define COM_ALPHA_LEN		8
#define COM_OMEGA_LEN		10
#define COM_LVL2_LEN		4

#define MAX_COM_LEN			COM_REMOTE_LEN

// En millisecondes
#define REMOTE_INTERVAL		250
#define ALPHA_INTERVAL		75
#define OMEGA_INTERVAL		150
#define TIMEOUT_INTERVAL	350

#define TIMEOUT_COUNT_MAX	4

#ifndef OFFLINE
	#define OFFLINE			0
#endif

#ifndef ONLINE
	#define ONLINE			1
#endif

#define UNLOCKED			0
#define LOCKED				1

class HydraRF
{
  public
	HydraRF(const int pinEN, const int pinCSN); 						   // Constructeur pour les tanks.
	HydraRF(_SPI* PtrSPI,const int pinEN, const int pinCSN);			    // Construteur pour la remote.
	
	
	void init (void);						   // Initialise les variables et les canaux de communication.
	
												   // Part un ticker récurant de TIMEOUT_INTERVAL pour la 
												            // vérification du status de la communication.
															
										            // Part un ticker récurant de REMOTE_INTERVAL pour la
										                   // transmission de la trame (Remote seulement).
													  
													  
	void update (void);	                        // Fait un Network update et lit les transmissions reçues.
	
							                         // Seul les transmissions commencant par GO et ayant
													   // un bon checksum seront considérées comme valide.
													   
											   // La reception d'une communication de la remote déclanche 
												 // un ticker de ALPHA_INTERVAL ou OMEGA_INTERVAL pour la
												           // transmission de la réponse (Tank seulement).
														   
												    // La réception d'une communication d'un tank modifie
																	   // l'état du lock (Tank Seulement).

													   // En cas de perte de communication les directives
														// des tanks sont remises à zero (Tank Seulement).																	   
	
	struct sCom ComRemote;					     // Structure pour le data de la remote(voir Structure.h).
	
	#ifndef OMEGA
	AlphaToRemoteCommunicationFormat TrameAlpha;// Structure pour le data du tank Alpha(voir Structure.h).
	#endif
	
	#ifndef ALPHA	
	struct sComOmega ComOmega;                 // Structure pour le data du tank Omega (voir Structure.h).
	#endif
	
	#ifndef REMOTE
	bool getStatus(void);				      // Retourne le status de la communication (Tanks seulement).
	
	bool getLockStatus(void);				               // Retourne le status du lock (Tank seulement).
	#endif
	
	#ifdef REMOTE
	bool getStatusAlpha(void);	                                // Retourne le status de la communication 
	                                                             // avec le tank Alpha (Remote seulement).
	
	bool getStatusOmega(void);	                                // Retourne le status de la communication 
	                                                             // avec le tank Omega (Remote seulement).
																 
										// Si les deux méthodes retourne OFFLINE, il y a réinitialisation
										// récurante de la communication jusqu'à la lecture d'une réponse.
	#endif
	
  private
	void receive (void);
	void transmit (void);
	void check_timeout (void);
	
	bool flagTX;
	const int Adrs[5] = {00,01,012,02,011};
	unsigned char dataRX[MAX_COM_LEN];
	unsigned char dataTX[MAX_COM_LEN];
	unsigned char firstbyte;
	unsigned char secondbyte;
	
	#ifdef REMOTE
	bool statusAlpha;
	bool statusOmega;
	unsigned char count_alpha;
	unsigned char count_omega;
	#endif
	
	
	#ifndef REMOTE
	bool status;
	bool lock;
	bool level;
	unsigned char count_timeout;	
	#endif		
};
 #endif
 */