/***********************************************
       robocup 2023
       arduino uno
       master des trois modules

************************************************/

//=============================
// inclusion des bibliotheques
//=============================
// je charge la bibliothèque qui nous permet de communiquer
// avec les composants utilisant le protocole de liaison I2C
#include <Wire.h>
#include "fonctions.h"  // fichier des fonctions
#include "variables.h"  // fichier des variables
#include "commandes.h"  // fichier des commandes

//======================
// adresses des modules
//======================
// Définition des adresses logiques des esclaves I2C.
// 11 bras, 12 convoyeur et 14 portique
#define I2C_SLAVE_ADDRESS_BRAS  11
#define I2C_SLAVE_ADDRESS_CONVOYEUR  12
#define I2C_SLAVE_ADDRESS_PORTIQUE  14

//=======
// setup
//=======
// ---------------------------------------------------------------------------
// Un programme Arduino doit imperativement contenir la fonction "setup"
// Elle ne sera executee qu'une seule fois au demarrage du microcontroleur
// Elle sert a configurer globalement les entrees sorties
// ---------------------------------------------------------------------------
void setup()
{
  // Ouvre le port serie et fixe le debit de communication a 9600 bauds
  Serial.begin(SERIAL_BAUD);

  // Initialise la library Wire et se connecte au bus I2C en tant que master
  Wire.begin();

  values = "mv10";
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);

}

//=====
// loop
//=====
// ---------------------------------------------------------------------------
// Le programme principal s’execute par une boucle infinie appelee loop()
// ---------------------------------------------------------------------------
void loop() {
  //delay(1000);
  values = "sc";  // demande etat objet sur le convoyeur
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);    // envoi i2c
  Wire.requestFrom(I2C_SLAVE_ADDRESS_CONVOYEUR, 1);  // lecture de la valeur en retour
  while (Wire.available())  {                        // attente des octets i2c
    char c = Wire.read();
    if ( c == 1 ) {
      Serial.println("objet absent ");
      values = "START";
      SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
    } else {
      Serial.println("objet present ");
      values = "STOP";
      SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
    }
  }
}
