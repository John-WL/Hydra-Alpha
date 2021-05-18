// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "peripheral/wifi_server_hydra/WiFiServerHydra.h"

void setup()
{
    Serial.begin(115200);
    WiFiServerHydra::init();
}

void loop()
{
    WiFiServerHydra::update([](websockets::WebsocketsMessage* messages, uint8_t amountOfMessages)
    {
        // Remplacer ce commentaire par l'accès au SPIFF, et l'écriture dans le fichier, etc.
        // Dans cette scope, il est possible d'accèder aux variables "messages" et "amountOfMessages".
        // - "messages" est un array[2] de WebsocketsMessage. Il contient le(s) message(s) reçu(s) (supposément le data JPEG provenant de(s) caméra(s));
        // - "amountOfMessages" est un uint8_t qui vaut 1 ou 2. Il vaut 1 si 1 seul message a été reçu, et
        //   vaut 2 si 2 messages ont été reçus en même temps.

        // La variable "amountOfMessages" n'est utile que lorsque la double réception est définie.
        // Si la double réception n'est pas définie, "amountOfMessages" sera toujours égale à 1,
        // et on ne reçevra qu'un seul message à la fois dans cette scope. 
        // Pour définir la double réception, il faut aller dans "WiFiServerHydra.h", et décommenter
        // la ligne "//#define ENABLE_SIMULTANEOUS_RECEPTION" en haut du fichier. 
        // Juste à la garder commentée si la simple réception est désirée. 

        // code de base pour afficher la grosseur des trames reçues
        Serial.print("Nombre de bytes reçu par le client #1: ");
        Serial.println(messages[0].length());

        if(amountOfMessages == 2)
        {
            Serial.print("Nombre de bytes reçu par le client #2: ");
            Serial.println(messages[1].length());
        }
    });
}
