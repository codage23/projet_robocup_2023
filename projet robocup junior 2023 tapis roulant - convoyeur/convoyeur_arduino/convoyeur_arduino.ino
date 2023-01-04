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

    // reception du message mvxx vitesse rpm
    if (message[0] == 109 and message[1] == 118) { // m motor et v vitesse speed
      // Extract only the number. E.g. from "mv10" to "10"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorSpeed = atoi(dataInS); // char to int
      Serial.println(motorSpeed);
    }

    // reception du message mpxx pas
    if (message[0] == 109 and message[1] == 112) { // m motor et p pas
      // Extract only the number. E.g. from "mv120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorStep = atoi(dataInS); // char to int
      Serial.println(motorStep);
    }
    // reception du message msx sens
    if (message[0] == 109 and message[1] == 115) { // m motor et s sens
      // Extract only the number. E.g. from "ms1" to "1"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorInverse = atoi(dataInS); // char to int
      Serial.println(motorInverse);
    }
    // reception du message STOP
    if (message[0] == 83 and message[1] == 84 and message[2] == 79 and message[3] == 80) {  // STOP
      stopStart = 0;
      Serial.println(stopStart);
    }
    // reception du message START
    if (message[0] == 83 and message[1] == 84 and message[2] == 79 and message[3] == 80) {  // START
      stopStart = 1;
      Serial.println(stopStart);
    }
  }
}
#endif

bool sensorIR() {
  int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input
  // Check if the pin high or not
  if (sensorStatus == 1)   {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW); // LED LOW
    Serial.println("objet absent");      // print Motion Detected! on the serial monitor window
  }
  else  {
    //else turn on the onboard LED
    digitalWrite(LED, HIGH);                 // LED High
    Serial.println("objet present");         // print Motion Ended! on the serial monitor window
  }
  return sensorStatus;
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Demarrage du convoyeur avec le sensor ir");

  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(LED, OUTPUT);     // LED Pin Output

#if I2C and !TEST
  // Initialise la library Wire et se connecte au bus I2C en tant qu'esclave
  Wire.begin(I2C_SLAVE_CONVOYEUR);
  // Définition de la fonction qui prendra en charge les informations recues sur le bus I2C
  Wire.onReceive(fonctionI2C);
#endif
}

void loop() {
  MyStepper.setSpeed(motorSpeed); //  rpm
  if  (sensorIR() and stopStart) {
    Serial.println(motorSpeed);
    if (!motorInverse) {
      Serial.println(-motorStep);
      MyStepper.step(-motorStep); // do -xxx steps in the other direction
    } else {
      Serial.println(motorStep);
      MyStepper.step(motorStep); // do -xxx steps in the other direction
    }
  } else {
    /*
      Serial.println(motorSpeed);
      if (!motorInverse) {
      Serial.println(motorStep);
      MyStepper.step(motorStep); // xxx steps corresponds to one revolution in one minute for 1 rpm
      } else {
      Serial.println(-motorStep);
      MyStepper.step(-motorStep); // do -xxx steps in the other direction
      }
    */
  }
  
  // fonction  d'attente i2c
#if I2C and !TEST
  fonctionI2C();
#endif

}
