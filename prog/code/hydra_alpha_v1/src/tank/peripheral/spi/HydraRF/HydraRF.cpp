#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <UniversalTimer.h>

#include "HydraRF.h"
#include "Structure.h"

// Lexique *****************************************************
#ifdef REMOTE
  #define CE_NODE         ADRS_REMOTE
#endif

#ifdef ALPHA
  #define CE_NODE         ADRS_ALPHA
  #define CE_NODE_LVL2    ADRS_ALPHA_LVL2
#endif

#ifdef OMEGA
  #define CE_NODE         ADRS_OMEGA
  #define CE_NODE_LVL2    ADRS_OMEGA_LVL2
#endif        

#define LVL1              false
#define LVL2              true

// Fonctions ***************************************************

void transmit (void);
void transmit_multicast (void);
void receive (void);
void check_timeout(void);

#ifdef REMOTE
  void load_ComRemote (void);
  void unload_ComOmega (void);
  void unload_TrameAlpha (void);
#endif

#ifndef REMOTE
  void unload_ComRemote (void);
#endif 

#ifdef OMEGA
  void load_ComOmega (void);
#endif

#ifdef ALPHA
  void load_TrameAlpha (void);
#endif

// Objets *******************************************************

RF24 myRF(CE,CSN);
RF24Network myNetwork(myRF);

#ifdef REMOTE
  UniversalTimer timerTX(DELAY_TX_REMOTE,true);
#endif

UniversalTimer timerTimeout(DELAY_TIMEOUT,true);

// Variables *****************************************************

unsigned char dataRX[COM_REMOTE_LEN+3] = {0,0,0,0,0,0,0,0,0,0,0};

#ifndef REMOTE
  bool state_RF = OFFLINE;
  unsigned char count_timeout = 0;
#endif

#ifdef REMOTE
  bool state_RF_Alpha = OFFLINE;
  bool state_RF_Omega = OFFLINE;
  unsigned char count_alpha = 0;
  unsigned char count_omega = 0;
  unsigned char dataTX[COM_REMOTE_LEN+3] = {0,0,0,0,0,0,0,0,0,0,0}; 
#endif

#ifdef ALPHA
  unsigned char dataTX[COM_ALPHA_LEN+3] = {0,0,0,0,0,0,0,0};
#endif

#ifdef OMEGA
  unsigned char dataTX[COM_OMEGA_LEN+3] = {0,0,0,0,0,0,0,0,0,0};
#endif

// Structure *****************************************************

struct sCom ComRemote;                  
 
#ifndef OMEGA
  AlphaToRemoteCommunicationFormat TrameAlpha; 
#endif

#ifndef ALPHA
  struct sComOmega ComOmega;              
#endif

//************************************************************************//

void init_RF (void)
{
    ComRemote.alpha.mode            =   0x00;
    ComRemote.alpha.moteur.full     =   0x00;
    ComRemote.alpha.camera.full     =   0x00;
    ComRemote.alpha.distance        =   0x00;
    ComRemote.omega.mode            =   0x00;
    ComRemote.omega.moteur.full     =   0x00;
    ComRemote.omega.camera.full     =   0x00;
    ComRemote.omega.distance        =   0x00;
  
   #ifndef OMEGA
    TrameAlpha.batteryLevel         =   0x00;
    TrameAlpha.distanceSonar.full   =   0x00;
    TrameAlpha.mode                 =   0x00;
    TrameAlpha.error                =   0x00;
  #endif  
  
  #ifndef ALPHA
    ComOmega.mainBat                =   0x00;
    ComOmega.spareBat               =   0x00;
    ComOmega.mode                   =   0x00;
    ComOmega.distance.full          =   0x00;
    ComOmega.sigStrength            =   0x00;
    ComOmega.error                  =   0x00; 
  #endif

  #ifdef DEBUG_RF_ON
    Serial.begin(115200);
  #endif
  
  SPI.begin();
  myRF.begin();
  myRF.setDataRate(RF24_2MBPS);
  myRF.setPALevel(RF24_PA_MAX);
  myNetwork.begin(CE_NODE);

  #ifndef REMOTE
    myNetwork.multicastRelay = true;
  #endif
  
  timerTimeout.start();
  
  #ifdef REMOTE
    timerTX.start();
  #endif
}

//************************************************************************//

void update_RF (void)
{
  receive();
  #ifdef REMOTE
    if(timerTX.check())transmit_multicast();
  #endif
  if(timerTimeout.check())check_timeout();
}

//************************************************************************//

void transmit (void)
{  
  int i;
  
  RF24NetworkHeader header_outgoing(ADRS_REMOTE,'C');
  
  #ifdef ALPHA
    load_TrameAlpha();
  #endif

  #ifdef OMEGA
    load_ComOmega();
  #endif
  
  myNetwork.write(header_outgoing,dataTX,sizeof(dataTX));

  #ifdef DEBUG_RF_TX_HEADER
    Serial.println(header_outgoing.toString());
    Serial.println("");
  #endif

  #ifdef DEBUG_RF_TX_DATA
    #ifdef ALPHA
      for(i=0;i<COM_ALPHA_LEN+3;i++)
      {
        Serial.print(dataTX[i], HEX);
        Serial.print(" ");
      }
    #endif
    #ifdef OMEGA
      for(i=0;i<COM_OMEGA_LEN+3;i++)
      {
        Serial.print(dataTX[i], HEX);
        Serial.print(" ");
      }
    #endif
    Serial.println("");
    Serial.println("");
  #endif
}

//************************************************************************//

void transmit_multicast (void)
{
  int i;
  
  RF24NetworkHeader header_outgoing;
  header_outgoing.type = 'C';

  #ifdef REMOTE
    load_ComRemote();
  #endif
  
  myNetwork.multicast(header_outgoing,dataTX,sizeof(dataTX),1);

  #ifdef DEBUG_RF_TX_HEADER
    Serial.println(header_outgoing.toString());
    Serial.println("");
  #endif

  #ifdef DEBUG_RF_TX_DATA
    for(i=0;i<COM_REMOTE_LEN+3;i++)
    {
      Serial.print(dataTX[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");
    Serial.println("");
  #endif
  
}

//************************************************************************//

void receive (void)
{    
  unsigned char check_sum;
  int i;
  
  myNetwork.update();                                                             // Rafraichit l'information du nRF24.
  while (myNetwork.available())                            // Boucle pour la lecture de tous les messages dans le FIFO.
  {    
    RF24NetworkHeader header_incoming;
    
    myNetwork.peek(header_incoming);                                                              // Lecture du header.
    
    if(header_incoming.type == 'C')                                                              // Validation du type.
    {
      for(i=0;i<COM_REMOTE_LEN+3;i++) dataRX[i] = 0;                                                   // Reset buffer.
      
      myNetwork.read(header_incoming,dataRX,sizeof(dataRX));                                                   // Read.    

      if((dataRX[0] == 'G') && (dataRX[1] == 'O'))                                          // Validation des préfixes.
      {
        check_sum = 0;

        #ifdef DEBUG_RF_RX_HEADER
          Serial.println(header_incoming.toString());
          Serial.println(""); 
        #endif
        
        switch (header_incoming.from_node)                                                  // Validation de l'adresse.
        {
          #ifndef REMOTE
            case ADRS_REMOTE: 
              for(i = 0; i < COM_REMOTE_LEN+2; i++) check_sum += dataRX[i];
              
              if (check_sum != dataRX[COM_REMOTE_LEN+2]) return; // Validation du check_sum avec sortie en cas d'échec. 
                        
              unload_ComRemote();                                                        // Enregistrement des données.                                       
              state_RF = ONLINE;
              count_timeout = 0;

              #ifdef DEBUG_RF_RX_DATA
                for(i=0;i<COM_REMOTE_LEN+3;i++)
                {
                  Serial.print(dataRX[i], HEX);
                  Serial.print(" ");
                }
                Serial.println("");
                Serial.println(""); 
              #endif 
              
              transmit();                                                                       // Envoi de la réponse.
            break;
          #endif
          
          #ifdef REMOTE  
            case ADRS_ALPHA:
            case ADRS_ALPHA_LVL2:
              for(i = 0; i < COM_ALPHA_LEN+2; i++) check_sum += dataRX[i];
              
              if (check_sum != dataRX[COM_ALPHA_LEN+2]) return; // Validation du check_sum avec sortie en cas d'échec.  
                         
              unload_TrameAlpha();                                                      // Enregistrement des données.
              state_RF_Alpha = ONLINE;
              count_alpha = 0;

              #ifdef DEBUG_RF_RX_DATA
                for(i=0;i<COM_ALPHA_LEN+3;i++)
                {
                  Serial.print(dataRX[i], HEX);
                  Serial.print(" ");
                }
                Serial.println("");
                Serial.println("");  
              #endif
            break;
              
            case ADRS_OMEGA:
            case ADRS_OMEGA_LVL2:
              for(i = 0; i < COM_OMEGA_LEN+2; i++) check_sum += dataRX[i];
              
              if (check_sum != dataRX[COM_OMEGA_LEN+2]) return; // Validation du check_sum avec sortie en cas d'échec.  
                       
              unload_ComOmega();                                                        // Enregistrement des données.
              state_RF_Omega = ONLINE;
              count_omega = 0;

              #ifdef DEBUG_RF_RX_DATA
                for(i=0;i<COM_OMEGA_LEN+3;i++)
                {
                  Serial.print(dataRX[i], HEX);
                  Serial.print(" ");
                }
                Serial.println("");
                Serial.println(""); 
              #endif                       
            break;
          #endif  
        }
      }      
    }
  }
}

//************************************************************************//

void check_timeout (void)
{  
  #ifndef REMOTE
    static bool level = LVL1;
    
    count_timeout++;
    if(count_timeout == TIMEOUT_MAX_COUNT+1)              // Nombre TIMEOUT_MAX_COUNT de communications manquées avant
    {                                                                                       // une déclaration OFFLINE.
      count_timeout = 0;
      
      state_RF = OFFLINE;

                                                  // Arrêt automatique des mouvements en cas de perte de communication.
      #ifdef ALPHA
        ComRemote.alpha.moteur.full     =   0x00;
        ComRemote.alpha.camera.full     =   0x00;
        ComRemote.alpha.distance        =   0x00;
      #endif
      
      #ifdef OMEGA
        ComRemote.omega.moteur.full     =   0x00;
        ComRemote.omega.camera.full     =   0x00;
        ComRemote.omega.distance        =   0x00; 
      #endif

                                                                                        // Connection à un nouveau node.
      level = !level;
      if(level == LVL2) myNetwork.begin(CE_NODE_LVL2);
      else myNetwork.begin(CE_NODE);       
    }

    #ifdef DEBUG_RF_STATE_COM
      if(count_timeout == 0) Serial.println("trying new node"); 
      else if (count_timeout != 1)Serial.println("trying to reconnect");
      Serial.println(""); 
    #endif    
  #endif

  #ifdef REMOTE
    static unsigned char count_silence = COUNTDOWN_TO_RESET;
    
    if(count_alpha < 255) count_alpha++;
    if(count_alpha == TIMEOUT_MAX_COUNT+1) state_RF_Alpha = OFFLINE;       // Nombre TIMEOUT_MAX_COUNT de communications 
                                                                               // manquées avant une déclaration OFFLINE.
    
    if(count_omega < 255) count_omega++;
    if(count_omega == TIMEOUT_MAX_COUNT+1) state_RF_Omega = OFFLINE;       // Nombre TIMEOUT_MAX_COUNT de communications 
                                                                               // manquées avant une déclaration OFFLINE.
                                                                               

    if ((state_RF_Alpha == OFFLINE) && (state_RF_Omega == OFFLINE))count_silence--;    // Compte à rebour avant un reset
                                                                                                  // de la communication.
    
    if ((state_RF_Alpha == ONLINE) || (state_RF_Omega == ONLINE))count_silence = COUNTDOWN_TO_RESET; // Reset du compte à rebour. 
    
    if(count_silence == 0)                                                                            // Reset du réseau.
    {
      count_silence = COUNTDOWN_TO_RESET;
      myNetwork.begin(CE_NODE);
    }

    #ifdef DEBUG_RF_STATE_COM
      if(count_alpha != 1)
      {
        if (count_alpha  < TIMEOUT_MAX_COUNT+1) Serial.println("waiting for alpha");
        else Serial.println("alpha offline");
            
      }
      if(count_omega != 1)      
      {
        if(count_omega < TIMEOUT_MAX_COUNT+1) Serial.println("waiting for omega");
        else Serial.println("omega offline");
        Serial.println(""); 
      }
      
    #endif
  #endif
  
}

//*************** Fonctions de tranfère de buffer ***************************

#ifdef OMEGA
  //************************************************************************//
  
  void load_ComOmega (void)
  {
    unsigned char check_sum = 0;
    
    dataTX[0] = 'G';
    dataTX[1] = 'O';
    dataTX[2] = ComOmega.mainBat;
    dataTX[3] = ComOmega.spareBat;
    dataTX[4] = ComOmega.mode;
    dataTX[5] = ComOmega.distance.split.lsb;
    dataTX[6] = ComOmega.distance.split.msb;
    dataTX[7] = ComOmega.sigStrength;
    dataTX[8] = ComOmega.error;
    for(int i = 0; i < COM_OMEGA_LEN+2; i++) check_sum += dataTX[i];
    dataTX[9] = check_sum;
  }
#endif

#ifdef ALPHA
  //************************************************************************//
  
  void load_TrameAlpha (void)
  {
    unsigned char check_sum = 0;
    
    dataTX[0] = 'G';
    dataTX[1] = 'O';
    dataTX[2] = TrameAlpha.batteryLevel;  
    dataTX[3] = TrameAlpha.distanceSonar.split.lsb; 
    dataTX[4] = TrameAlpha.distanceSonar.split.msb; 
    dataTX[5] = TrameAlpha.mode;  
    dataTX[6] = TrameAlpha.error;
    for(int i = 0; i < COM_ALPHA_LEN+2; i++) check_sum += dataTX[i];
    dataTX[7] = check_sum;
  }
#endif

#ifndef REMOTE
  //************************************************************************//
  
  void unload_ComRemote (void)
  {
    #ifdef ALPHA
      ComRemote.alpha.mode            =   dataRX[2];
      ComRemote.alpha.moteur.full     =   dataRX[3];
      ComRemote.alpha.camera.full     =   dataRX[4];
      ComRemote.alpha.distance        =   dataRX[5];                                                   
    #endif
    
    #ifdef OMEGA
      ComRemote.omega.mode            =   dataRX[6];
      ComRemote.omega.moteur.full     =   dataRX[7];
      ComRemote.omega.camera.full     =   dataRX[8];
      ComRemote.omega.distance        =   dataRX[9];                                                               
    #endif
  }
#endif

#ifdef REMOTE
  //************************************************************************//
  
  void unload_ComOmega (void)
  {
    ComOmega.mainBat                    =   dataRX[2];
    ComOmega.spareBat                   =   dataRX[3];
    ComOmega.mode                       =   dataRX[4];
    ComOmega.distance.split.lsb         =   dataRX[5];
    ComOmega.distance.split.msb         =   dataRX[6];
    ComOmega.sigStrength                =   dataRX[7];
    ComOmega.error                      =   dataRX[8];
  }
  
  //************************************************************************//
  
  void unload_TrameAlpha (void)
  {
    TrameAlpha.batteryLevel             =   dataRX[2];
    TrameAlpha.distanceSonar.split.lsb  =   dataRX[3];
    TrameAlpha.distanceSonar.split.msb  =   dataRX[4];
    TrameAlpha.mode                     =   dataRX[5];
    TrameAlpha.error                    =   dataRX[6];
  }

  //************************************************************************//

  void load_ComRemote (void)
  {
    unsigned char check_sum = 0;
    
    dataTX[0] = 'G';
    dataTX[1] = 'O';
    dataTX[2] = ComRemote.alpha.mode;
    dataTX[3] = ComRemote.alpha.moteur.full;
    dataTX[4] = ComRemote.alpha.camera.full;
    dataTX[5] = ComRemote.alpha.distance;
    dataTX[6] = ComRemote.omega.mode;
    dataTX[7] = ComRemote.omega.moteur.full;
    dataTX[8] = ComRemote.omega.camera.full;
    dataTX[9] = ComRemote.omega.distance;
    for(int i = 0; i < COM_REMOTE_LEN+2; i++) check_sum += dataTX[i];
    dataTX[10] = check_sum;
  }
#endif
//************************************************************************//
