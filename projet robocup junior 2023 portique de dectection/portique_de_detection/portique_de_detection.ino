/***********************************************
  projet robocup 2023 - portique detection
        jlm janv 2023

  pc : pour renvoyer la couleur detectee  10 rouge, 20 verte, 30 bleue
  pl : pour la deuxieme led : 0 eteinte, 1 rouge, 2 verte, 3 bleue
  RESET pour remise a zero du portique

************************************************/

//=============================
// inclusion des bibliothèques
//============================
#include <Wire.h> //composants utilisant le protocole I2C
#include "variables.h"


bool SensorIr() {
  // The program reads the current status of the sensor pin and
  // displays in the serial console whether an obstacle is currently detected
  // or if there is no obstacle in front of the sensor
  // The current signal at the sensor is read out
  bool val = digitalRead(IRSensor);
  if (val == HIGH) {
    //Serial.println("No obstacle");
  } else {
    //Serial.println("Obstacle detected");
  }
  return val;
}

void getFrequency() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // redColor = map(redFrequency, 70, 120, 255,0);
  // redColor = map(redFrequency, XX, XX, 255,0);
  frequencyRed = pulseIn(sensorOut, LOW);
  red_value = map(frequencyRed, 20, 130, 255, 0);
  if (DEBUG) {
    Serial.print("Rouge = ");
    Serial.print(frequencyRed);
    Serial.print("   ");
    Serial.print(red_value);
    Serial.print("  ");
  }

  delay(100);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  // greenColor = map(greenFrequency, XX, XX, 255, 0);
  frequencyGreen = pulseIn(sensorOut, LOW);
  green_value = map(frequencyGreen, 30, 150, 255, 0);
  if (DEBUG) {
    Serial.print("Verte= ");
    Serial.print(frequencyGreen);
    Serial.print("   ");
    Serial.print(green_value);
    Serial.print("  ");
  }

  delay(100);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  // blueColor = map(blueFrequency, XX, XX, 255, 0);
  frequencyBlue = pulseIn(sensorOut, LOW);
  blue_value = map(frequencyBlue, 20, 130, 255, 0);
  if (DEBUG) {
    Serial.print("Bleu= ");
    Serial.print(frequencyBlue);
    Serial.print("   ");
    Serial.print(blue_value);
    Serial.print("  ");
    delay(100);
  }
}

int checkColor() {
  if ((red_value > green_value) && (red_value > blue_value) && (frequencyRed < 130)) {
    if (DEBUG) {
      Serial.print(red_value);
      Serial.print("  ");
      Serial.print(green_value);
      Serial.print("  ");
      Serial.print(blue_value);
      Serial.println(" RED detected!");
    }
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);

    couleur = 1; // rouge

  } else  if ((green_value > red_value) && (green_value > blue_value) && (frequencyGreen < 150)) {
    if (DEBUG) {
      Serial.print(red_value);
      Serial.print("  ");
      Serial.print(green_value);
      Serial.print("  ");
      Serial.print(blue_value);
      Serial.println(" GREEN detected!");
    }
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, LOW);

    couleur = 2; // verte

  } else  if ((blue_value > red_value) && (blue_value > green_value) && (frequencyBlue < 130)) {
    if (DEBUG) {
      Serial.print(red_value);
      Serial.print("  ");
      Serial.print(green_value);
      Serial.print("  ");
      Serial.print(blue_value);
      Serial.println(" BLUE detected!");
    }
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, HIGH);

    couleur = 3; // bleue

  } else {
    Serial.println(" no detected!");
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);

    couleur = 0; // sans
  }
  return couleur;
}

#if I2C and !TEST
void receiveEvents() {
  // Check for incoming data
  // Lecture du module I2C
  if (Wire.available() > 0) {
    // raz du message
    for (int i = 0; i < MAX_MESSAGE_LENGTH; i++) {
      message[i] = '\0';
    }
    // prints the received data
    //Serial.print("I received: ");
    for (int i = 0; i < MAX_MESSAGE_LENGTH ; i++) {
      dataI2C =  Wire.read(); // lecture de l'i2c
      if (dataI2C == 0xFFFFFFFF ) {  // fin du message avant la longueur maxi
        break;
      }
      message[i] = dataI2C;  // constitution du message
      //Serial.print(dataI2C,HEX);
      //Serial.print(message[i]);
    }
    //Serial.println("");
    //int taille = sizeof(message); // taille du tableau
    int taille = strlen(message);   // taille de la chaine
    //Serial.println(taille);
    char dataInS[taille];

    // demande couleur  pc
    if (message[0] == 112 and message[1] == 99) { // p et c
      requestI2C = 1; // demande du master i2c
      //Serial.println(requestI2C);
    }

    // allumage led1 multicolor  pl(xx)
    if (message[0] == 112 and message[1] == 108 ) { // p et l
      // Extract only the number from "pl10" to "10"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      resultatLed1 = atoi(dataInS); // char to int
      //Serial.println(resultatLed1);
      if (resultatLed1 == 10) {        // rouge
        digitalWrite(ledRed1, HIGH);
        digitalWrite(ledGreen1, LOW);
        digitalWrite(ledBlue1, LOW);
      } else if (resultatLed1 == 20) { // verte
        digitalWrite(ledRed1, LOW);
        digitalWrite(ledGreen1, HIGH);
        digitalWrite(ledBlue1, LOW);
      } else if (resultatLed1 == 30) { // bleue
        digitalWrite(ledRed1, LOW);
        digitalWrite(ledGreen1, LOW);
        digitalWrite(ledBlue1, HIGH);
      } else {                         // eteinte
        digitalWrite(ledRed1, LOW);
        digitalWrite(ledGreen1, LOW);
        digitalWrite(ledBlue1, LOW);
      }
    }

    // If button "RESET" is pressed  raz du portique
    if (message[0] == 82 and message[1] == 69 and message[2] == 83 and message[3] == 69 and message[4] == 84) { // RESET
      digitalWrite(ledRed1, LOW);
      digitalWrite(ledGreen1, LOW);
      digitalWrite(ledBlue1, LOW);

      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);

      couleur = 0;
      int sensor_ir = 0;            // variable pour l'etat actuel du bouton poussoir
      int sensor_ir_mem = 0;        // variable pour l'etat precedent du bouton poussoir
    }
  }
}
#endif

#if I2C and !TEST
void requestEvents() {
  if (requestI2C) {
    //Serial.print(" couleur request :  ");
    //Serial.println(couleur);
    Wire.write(couleur);
  } else {
    requestI2C = 0;
  }
}
#endif

void portiqueIR () {
  delay(30); // eviter les pics
  sensor_ir = SensorIr();  // lit l'etat actuel du sensor IR
  //Serial.println(sensor_ir);
  //Serial.println(sensor_ir);
  // compare l'etat actuel du sensor IR a l'etat precedent memorise
  if (sensor_ir != sensor_ir_mem) {      // si l'etat du sensor IR a change
    // on memorise l'etat courant du sensor IR pour les prochains passages dans la boucle loop
    sensor_ir_mem = sensor_ir;
    // si ce nouvel etat est passe a 1, on a donc un front montant.
    if (sensor_ir == 1) {
      digitalWrite(ledsBlanches, LOW); // leds blanches pour le detecteur de couleur allumage
      delay(300);
      getFrequency(); // test les differentes couleurs
      checkColor();   // selectionne la bonne couleur
      delay(300);
      digitalWrite(ledsBlanches, HIGH); // leds blanches pour le detecteur de couleur extinction
    }
  }
}

//=======
// setup
//=======
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Demarrage du detecteur de couleurs");

  // led multicolor
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  // led multicolor 1
  pinMode(ledRed1, OUTPUT);
  pinMode(ledGreen1, OUTPUT);
  pinMode(ledBlue1, OUTPUT);

  // leds blanches du detecteur de couleurs
  pinMode(ledsBlanches, OUTPUT);

  // sensor ir
  pinMode(IRSensor, INPUT);  // Initialization of sensor pin

  // leds eteintes
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);

  digitalWrite(ledRed1, LOW);
  digitalWrite(ledGreen1, LOW);
  digitalWrite(ledBlue1, LOW);

  digitalWrite(ledsBlanches, HIGH);

  // init configuration  detecteur de couleur
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

#if I2C and !TEST
  // Initialise la library Wire et se connecte au bus I2C en tant qu'esclave
  Wire.begin(I2C_SLAVE_PORTIQUE);
  // Définition de la fonction qui prendra en charge les informations recues sur le bus I2C
  Wire.onReceive(receiveEvents);
  Wire.onRequest(requestEvents);
#endif
}

//=====
// loop
//=====
void loop() {
  portiqueIR();
}
