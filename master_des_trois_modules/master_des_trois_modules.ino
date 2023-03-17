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

  values = "mv14";                                 // vitesse du convoyeur a 14
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);  // commande envoyee i2c

}

//=====
// loop
//=====
// ---------------------------------------------------------------------------
// Le programme principal s’execute par une boucle infinie appelee loop()
// ---------------------------------------------------------------------------
void loop() {

  values = "pc";  // demande couleur
  SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE);    // commande envoiyee i2c
  Wire.requestFrom(I2C_SLAVE_ADDRESS_PORTIQUE, 1);  // lecture de la valeur en retour
  if (Wire.available())  {                          // attente des octets i2c
    char c = Wire.read();
    if ( c == 1 ) {     // couleur rouge detectee
      values = "pl10";  // led rouge
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // commande envoiyee i2c
      couleur = 10;
    } else if (c == 2) {  // couleur verte detectee
      values = "pl20";    // led verte
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // commande envoiyee i2c
      couleur = 20;
    } else if (c == 3) {  // couleur bleue detectee
      values = "pl30";    // led bleue
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // commande envoiyee i2c
      couleur = 30;
    } else {              // aucune couleur de detectee
      values = "pl00";    // led eteinte
      SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // commande envoiyee i2c
      couleur = 0;
    }
  }

  delay(300);

  values = "sc";  // demande etat objet sur le convoyeur
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);    // envoi i2cI2C_SLAVE_ADDRESS_PORTIQUE
  Wire.requestFrom(I2C_SLAVE_ADDRESS_CONVOYEUR, 1);  // lecture de la valeur en retour
  if (Wire.available())  {                           // attente des octets i2c
    char c = Wire.read();
    if ( c == 1 ) {                                  // pas d'objet en attente sur le convoyeur
      Serial.println("objet absent ");
      values = "START"; I2C_SLAVE_ADDRESS_PORTIQUE;   // commande START
      SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR); // commande envoiyee i2c
    } else {
      Serial.println("objet present ");
      values = "STOP";
      SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR); // commande envoiyee i2c
      if (couleur == 10) {    // couleur rouge
        positionAttente();    // fonction attente
        delay(1000);
        attraper();           // fonction attraper
        delay(1000);
        values = "s1130";     // taille position 130
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        values = "s3130";     // coude position 130
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        relacher();           // fonction relacher
        delay(1000);
        values = "s380";      // coude position 80
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        positionAttente();     // fonction attente
        delay(1000);
      } else if (couleur == 20) {  // couleur verte
        positionAttente();         // fonction attente
        delay(1000);
        attraper();                // fonction attraper
        delay(1000);
        values = "s175";           // taille position 75
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        values = "s3130";           // coude position 130
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        relacher();                 // fonction relacher
        delay(1000);
        values = "s380";            // coude position 80
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        positionAttente();          // fonction attente
        delay(1000);
      } else if (couleur == 30) { // couleur bleue
        positionAttente();        // fonction attente
        delay(1000);
        attraper();               // fonction attraper
        delay(1000);
        values = "s1100";         // taille position 100
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        values = "s2170";         // epaule position 170
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        values = "s3140";         // coude position 140
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        relacher();               // fonction relacher
        delay(1000);
        values = "s380";          // coude position 80
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        positionAttente();        // fonction attente
        delay(1000);
      } else {              // couleur = 0, donc un objet present mais la couleur n'est pas reconnue        
        positionAttente();  // fonction attente
        delay(1000);
        attraper();         // fonction attraper
        delay(1000);
        values = "s1160";    // taille position 160
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        values = "s2170";   // epaule position 170
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        values = "s3140";   // coude position 140
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        relacher();         // fonction relacher
        delay(1000);
        values = "s380";    // coude position 80
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
        delay(1000);
        positionAttente();  // fonction attente
        delay(1000);
      }
    }
  }
}
