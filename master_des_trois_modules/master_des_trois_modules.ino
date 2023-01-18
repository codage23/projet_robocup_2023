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

}

//=====
// loop
//=====
// ---------------------------------------------------------------------------
// Le programme principal s’execute par une boucle infinie appelee loop()
// ---------------------------------------------------------------------------
void loop() {

  if (nbTour == 1 ) {
    // demande à recevoir 1 octets du péripherique d'adresse 14
    values = "pc";  // demande couleur
    SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
    Wire.requestFrom(I2C_SLAVE_ADDRESS_PORTIQUE, 1);

    while (Wire.available())  {    // attente des octets i2c
      char c = Wire.read();
      if ( c == 1 ) {
        values = "pl10";  // led rouge
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
        delay(3000);
        values = "RESET";
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      } else if ( c == 2 ) {
        values = "pl20";  // led verte
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); //envoi i2c
        delay(3000);
        values = "RESET";
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      } else if ( c == 3 ) {
        values = "pl30"; // led bleue
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
        delay(3000);
        values = "RESET";
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      } else {
        values = "pl00";  // led eteinte
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE);
      }
      c = c + 48;  //  chiffre charactere ascii
      Serial.println(c);  // envoi à la console
    }
  }
}
/*
  if (nbTour == 1 ) {
    // repos WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // repos SHOULDER
    values = "s2180";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // repos ELBOW
    values = "s3100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // repos WRIST_ROLL
    values = "s4100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // repos WRIST_PITCH
    values = "s570";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // repos GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);

    delay(3000);

    // sequence
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // SHOULDER
    values = "s2140";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // ELBOW
    values = "s3150";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WRIST_ROLL
    values = "s4100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WRIST_PITCH
    values = "s580";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s670";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // ELBOW
    values = "s380";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s1120";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s10";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s1180";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);

    nbTour = 0;
  }
*/

/*
  values = "ss60";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
  values = "SAVE";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
  values = "RESET";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
  values = "RUN";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
*/
