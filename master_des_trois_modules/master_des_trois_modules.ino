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
void setup()   {
  // Ouvre le port serie et fixe le debit de communication a 9600 bauds
  Serial.begin(SERIAL_BAUD);

  Serial.println("demarrage master des trois modules");

  // Initialise la library Wire et se connecte au bus I2C en tant que master
  Wire.begin();
  /*
    values = "mv10";
    SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
  */
}

//=====
// loop
//=====
// ---------------------------------------------------------------------------
// Le programme principal s’execute par une boucle infinie appelee loop()
// ---------------------------------------------------------------------------
void loop() {

  values = "pc";  // demande couleur
  SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE);    // envoi i2c
  Wire.requestFrom(I2C_SLAVE_ADDRESS_PORTIQUE, 1);  // lecture de la valeur en retour
  if (Wire.available())  {                       // attente des octets i2c
    char c = Wire.read();
    if ( c == 1 ) {  // rouge
      values = "pl10";  // led rouge
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      couleur = 10;
    } else if (c == 2) {  // verte
      values = "pl20";  // led verte
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      couleur = 20;
    } else if (c == 3) { // bleue
      values = "pl30";  // led bleue
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      couleur = 30;
    } else { // aucune couleur de detectee
      values = "pl00";  // eteinte
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      couleur = 0;
    }
  }

  delay(300);

  values = "sc";  // demande etat objet sur le convoyeur
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);    // envoi i2c
  Wire.requestFrom(I2C_SLAVE_ADDRESS_CONVOYEUR, 1);  // lecture de la valeur en retour
  if (Wire.available())  {                        // attente des octets i2c
    char c = Wire.read();
    if ( c == 1 ) {
      Serial.println("objet absent ");
      values = "START";
      SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
    } else {
      Serial.println("objet present ");
      values = "STOP";
      SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
      if (couleur == 10) {  // rouge
        reposBras();       // mise au repos du bras
        delay(1000);
        positionAttente(); // position attente
        delay(1000);
        sequenceRouge();   // objet rouge
        delay(1000);
        positionAttente(); // position attente
        delay(1000);
      } else if (couleur == 20) {  // couleur verte
        reposBras();  // mise au repos du bras
        delay(1000);
        positionAttente(); // position attente
        delay(1000);
        sequenceVerte();  // objet verte
        delay(1000);
        positionAttente(); // position attente
      } else if (couleur == 30) {
        reposBras();  // mise au repos du bras
        delay(1000);
        positionAttente(); // position attente
        delay(1000);
        sequenceBleue();  // objet verte
        delay(1000);
        positionAttente(); // position attente
      } else {
      // couleur = 0
      }
    }
  }
}
