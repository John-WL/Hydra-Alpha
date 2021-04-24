Library a downloader:

RF24
RF24Network
UniversalTimer

Fichier à mettre dans le dossier:

HydraRf.h
HydraRF.c
Structure.h

La définition des pin CE et CSN doivent être ajusté
dans HydraRF.h pour celle de votre board.

L'identité doit être définit AVANT d'inclure HydraRF.h

Les fonctions de debuggage doivent être définit AVANT
d'inclure HydraRF.h 

Si vous utilisez un debuggage personalisé, DEBUG_RF_ON
doit être définit

La fonction init_RF doit être appelé dans le setup

La fonction update_RF doit être appelé dans le loop


Exemple d'utilisation:

#define REMOTE

#define DEBUG_RF

#include "HydraRF.h"

void setup() 
{
  init_RF();
}

void loop()
{
  update_RF();
}
