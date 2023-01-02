/***********************************************
  // Inclut la bibliothèque Arduino Stepper.h:
  // https://www.volta.ma/comment-utiliser-moteur-pas-a-pas-28byj-48-avec-pilote-uln2003-et-tutoriel-arduino/arduino/

        jlm dec 2022
************************************************/

//=============================
// inclusion des bibliothèques
//============================
#include <Stepper.h> // moteur pas a pas
#include <Wire.h> //composants utilisant le protocole I2C
#include "variables.h"


// Creez un objet stepper appele 'MyStepper', notez l'ordre des broches:
Stepper MyStepper(STEPS, 11, 9, 10, 8);  // IN1, IN3, IN2, IN4


#if I2C and !TEST
void fonctionI2C() {
  // Check for incoming data
  // Lecture du module I2C
  if (Wire.available() > 0) {
    // raz du message
    for (int i = 0; i < MAX_MESSAGE_LENGTH; i++) {
      message[i] = '\0';
    }
    // prints the received data
    Serial.print("I received: ");
    for (int i = 0; i < MAX_MESSAGE_LENGTH ; i++) {
      dataI2C =  Wire.read(); // lecture de l'i2c
      if (dataI2C == 0xFFFFFFFF ) {  // fin du message avant la longueur maxi
        break;
      }
      message[i] = dataI2C;  // constitution du message
      //Serial.print(dataI2C,HEX);
      Serial.print(message[i]);
    }
    Serial.println("");
    //int taille = sizeof(message); // taille du tableau
    int taille = strlen(message); // taille de la chaine
    Serial.println(taille);
    char dataInS[taille];
    // reception du message c1xx vitesse rpm
    if (message[0] == 99 and message[1] == 49) { // c et 1
      // Extract only the number. E.g. from "c110" to "10"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorSpeed = atoi(dataInS); // char to int
      Serial.println(motorSpeed);
      MyStepper.setSpeed(motorSpeed); //  rpm
    }
  }
}
#endif

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Demarrage du convoyeur");
#if I2C and !TEST
  // Initialise la library Wire et se connecte au bus I2C en tant qu'esclave
  Wire.begin(I2C_SLAVE_CONVOYEUR);
  // Définition de la fonction qui prendra en charge les informations recues sur le bus I2C
  Wire.onReceive(fonctionI2C);
#endif
  MyStepper.setSpeed(motorSpeed); //  rpm
  MyStepper.step(motorStep); // do 2038 steps -- corresponds to one revolution in one minute
}

void loop() {

  MyStepper.setSpeed(motorSpeed); //  rpm
  MyStepper.step(motorStep); // do 2038 steps -- corresponds to one revolution in one minute
  delay(500); // wait for one second
  MyStepper.step(motorStepInverse); // do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
  delay(500); // wait for one second
  /*
    #if I2C and !BLUETOOTH and !TEST
    fonctionI2C();
    #endif
  */
}
