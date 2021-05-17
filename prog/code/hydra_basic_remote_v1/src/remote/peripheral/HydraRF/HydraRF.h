// HydraRF.h & HydraRF.ino
//
// Implimentation d'un protocole de communication entre 3 module nRF24L01+.
//                                               (Remote, Alpha, Omega)
//
// Driver : SPI.h, RF24.h
// Interface: RF24Network.h 
// Process: HydraRF.h
// Service: Structure.h 
//
// Un seul doit être définit (obligatoire) AVANT d'inclure HydraRF.h
//
// #define REMOTE
// #define ALPHA
// #define OMEGA
//
// Ces fonctions offrent des communications automatisées avec des méchanismes de re-connection 
// en cas d'échec ainsi qu'une sauvegarde d'arrêt de mouvement automatique. 
//
// L'utilisation d'un réseau nodale permet le déplacement d'un node d'un niveau à un autre. 
//
// L'information (entrée et sortie) passe par l'utilisation de trois structures (voir Structure.h).
//

#ifndef HYDRARFH
  #define HYDRARFH

  #include "Structure.h"
  
  // Debuggage (à déclarer AVANT d'inclure HydraRF.h).
  // Peuvent être appelés individuellement ou en catégorie.
  // DEBUG_RF_ON doit être définit.
  
  // General:
  #ifdef DEBUG_RF
    #define DEBUG_RF_SLOW                             // Ralentie la communication par un facteur 10.
    #define DEBUG_RF_ON                               // Ouvre une communication sur le port série 0 à 115 200. 
    #define DEBUG_RF_TX_HEADER                        // Affiche le Header a chaque transmission.
    #define DEBUG_RF_TX_DATA                          // Affiche le data de chaque transmission.
    #define DEBUG_RF_RX_HEADER                        // Affiche le Header d'une réception après la première validation.
    #define DEBUG_RF_RX_DATA                          // Affiche le data d'une réception après les 5 validations.
    #define DEBUG_RF_STATE_COM                        // Affiche les états autre qu'ONLINE de la
  #endif                                              // communication de chaque tank.
    
  // Transmission:
  #ifdef DEBUG_RF_TX
    #define DEBUG_RF_SLOW
    #define DEBUG_RF_ON
    #define DEBUG_RF_TX_HEADER
    #define DEBUG_RF_TX_DATA
  #endif
  
  // Réception:
  #ifdef DEBUG_RF_RX
    #define DEBUG_RF_SLOW
    #define DEBUG_RF_ON
    #define DEBUG_RF_RX_HEADER
    #define DEBUG_RF_RX_DATA
  #endif
  
  // Status
  #ifdef DEBUG_RF_STATE
    #define DEBUG_RF_SLOW
    #define DEBUG_RF_ON
    #define DEBUG_RF_STATE_COM
  #endif
  
  // GPIO connecté sur le module nRF24L01+. 
  #define CE                      4
  #define CSN                     5

  // Lexique.
  #define OFFLINE                 false
  #define ONLINE                  true
  
  #ifndef TRUE
    #define TRUE                  1
  #endif
  
  #ifndef FALSE
    #define FALSE                 0
  #endif
  
  #define SERVO_LEFT              1
  #define SERVO_RIGHT             2                        
  
  #define SERVO_UP                1                        
  #define SERVO_DOWN              2

  #ifndef ALPHA_TO_REMOTE_LISTENING_TO_COMMANDS_MODE
    #define ALPHA_TO_REMOTE_LISTENING_TO_COMMANDS_MODE    0
  #endif
  
  #ifndef ALPHA_TO_REMOTE_SWARM_MODE
    #define ALPHA_TO_REMOTE_SWARM_MODE                    1
  #endif

  
  // Adresse nodale dans le réseau.
  #define ADRS_REMOTE             00                // Master.                                      
  #define ADRS_ALPHA              01                // Alpha level 1, node 1 du master.
  #define ADRS_ALPHA_LVL2         012               // Alpha level 2, node 1 de node 2.
  #define ADRS_OMEGA              02                // Omega level 1, node 2 du master.
  #define ADRS_OMEGA_LVL2         011               // omega level 2, node 1 de node 1.

  // Longueur des trames (excluant les préfixes et le check_sum).
  #define COM_REMOTE_LEN          6
  #define COM_ALPHA_LEN           5
  #define COM_OMEGA_LEN           7
  
  // Temporisation de la communication
  #ifndef DEBUG_RF_SLOW
    #define DELAY_TX_REMOTE         250             // Delai entre chaque envoi de trame de la remote (ms).
    #define DELAY_TIMEOUT           300             // Delai entre chaque vérification du timeout (ms).
  #endif                                            // DELAY_TX_REMOTE < DELAY_TIMEOUT < 2 * DELAY_TX_REMOTE
  

  #ifdef DEBUG_RF_SLOW
    #define DELAY_TX_REMOTE         2000              
    #define DELAY_TIMEOUT           3000              
  #endif
  
  #define TIMEOUT_MAX_COUNT       5                 // Nombre de timeout avant la transition offline.
                                                    // DELAY_TIMEOUT * TIMEOUT_MAX_COUNT = delai minimum avant un OFFLINE (ms).
                                                    // DELAY_TIMEOUT * TIMEOUT_MAX_COUNT = delai minimum avant un changement de node (ms) (Tanks seleument).
                                                    
  #define COUNTDOWN_TO_RESET      10                // Nombre de timeout entre les réinitialisations de la communication (Remote seulement). 
                                                    // DELAY_TIMEOUT * COUNTDOWN_TO_RESET = delai minimum avant un reset (ms) (Remote seulement). 
                                                    // (à partir du moment ou Alpha ET Omega sont OFFLINE) 
                                                   
                                                    
                                                    
  // Fonctions.
  void init_RF (void);                              // Débute le SPI, le module RF et le Network. Baudrate RF = 2MBPS. RF Power Amplification level = MAX.
                                                    // Part le timer du timeout.
                                                    // Part le timer de la transmission (Remote seulement).
                                                    // Part le relai multicast (Tanks seulement).
                                                    
  void update_RF (void);                            // Trois étapes principales: réception, transmission et vérification du timeout.
                                                    // La réception est bloquante jusqu'à ce que le FIFO du nRF soit vide. (En théorie max deux messages). 
                                                    // Validation des trames reçues en 5 points : type = 'C', dataRX[0] = 'G', dataRX[1] = 'O', adresse de l'expéditeur et check_sum.
                                                    // Les valeurs des trames valides seront stockées dans leur structure respective (voir plus bas).
                                                    // Sur réception d'une trame valide de la remote, les tanks transmettent leur trame réponse.
                                                    // La remote envoie sa trame (à interval régulier) à tout les nodes de level 1 (adresse nodale 01 et 02).
                                                    // Ceux-ci la retransmettent à tout les nodes de level 2 (adresse nodale 011 et 012).
                                                    

  // Variables.
  #ifndef REMOTE
    extern bool state_RF;                           // Status de la communication pour les tanks. (ex: if(state_RF == OFFLINE))
  #endif
  
  #ifdef REMOTE
    extern bool state_RF_Alpha;                     // Status de la communication avec Alpha.
    extern bool state_RF_Omega;                     // Status de la communication avec Omega.
  #endif
  

  // Structure d'entrée et sortie de la communication RF (voir Structure.h).    
  #ifndef OMEGA
    extern AlphaToRemoteCommunicationFormat TrameAlpha; // Accessible dans la remote et Alpha.
  #endif
  
  #ifndef ALPHA
    extern struct sComOmega ComOmega;               // Accessible dans la remote et Omega.
  #endif
  
  extern struct sCom ComRemote;                     // Accessible dans tous.
#endif
