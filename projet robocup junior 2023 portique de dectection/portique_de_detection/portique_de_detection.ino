/***********************************************

        jlm janv 2023
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
    Serial.println("No obstacle");
  } else {
    Serial.println("Obstacle detected");
  }
  return val;
}

void getFrequency() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  //// redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // redColor = map(redFrequency, 70, 120, 255,0);
  ////redColor = map(redFrequency, XX, XX, 255,0);
  frequencyRed = pulseIn(sensorOut, LOW);
  //red_value = frequencyRed;
  red_value = map(frequencyRed, 20, 130, 255, 0);
  Serial.print("Rouge = ");
  Serial.print(frequencyRed);
  Serial.print("  ");

  delay(100);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  ////greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  ////greenColor = map(greenFrequency, XX, XX, 255, 0);
  frequencyGreen = pulseIn(sensorOut, LOW);
  //green_value = frequencyGreen;
  green_value = map(frequencyGreen, 30, 150, 255, 0);
  Serial.print("Verte= ");
  Serial.print(frequencyGreen);
  Serial.print("  ");

  delay(100);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  ////blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  ////blueColor = map(blueFrequency, XX, XX, 255, 0);
  frequencyBlue = pulseIn(sensorOut, LOW);
  //blue_value = frequencyBlue;
  blue_value = map(frequencyBlue, 20, 130, 255, 0);
  Serial.print("Bleu= ");
  Serial.print(frequencyBlue);
  Serial.print("  ");
  delay(100);
}

int checkColor() {
  int couleur = 0;
  if ((red_value > green_value) && (red_value > blue_value) && (frequencyRed < 130)) {
    Serial.print(red_value);
    Serial.print("  ");
    Serial.print(green_value);
    Serial.print("  ");
    Serial.print(blue_value);
    Serial.println(" RED detected!");
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);

    couleur = 10; // rouge

    //digitalWrite(ledRed1, HIGH);
    //digitalWrite(ledGreen1, LOW);
    //digitalWrite(ledBlue1, LOW);

  } else  if ((green_value > red_value) && (green_value > blue_value) && (frequencyGreen < 150)) {
    Serial.print(red_value);
    Serial.print("  ");
    Serial.print(green_value);
    Serial.print("  ");
    Serial.print(blue_value);
    Serial.println(" GREEN detected!");
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, LOW);

    couleur = 20; // verte

    //digitalWrite(ledRed1, LOW);
    //digitalWrite(ledGreen1, HIGH);
    //digitalWrite(ledBlue1, LOW);

  } else  if ((blue_value > red_value) && (blue_value > green_value) && (frequencyBlue < 130)) {
    Serial.print(red_value);
    Serial.print("  ");
    Serial.print(green_value);
    Serial.print("  ");
    Serial.print(blue_value);
    Serial.println(" BLUE detected!");
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, HIGH);

    couleur = 30; // bleue

    //digitalWrite(ledRed1, LOW);
    //digitalWrite(ledGreen1, LOW);
    //digitalWrite(ledBlue1, HIGH);

  } else {
    Serial.println(" no detected!");
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);

    couleur = 0; // sans

    //digitalWrite(ledRed1, LOW);
    //digitalWrite(ledGreen1, LOW);
    //digitalWrite(ledBlue1, LOW);
  }
  return couleur;
}

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

    // If "Waist" slider has changed value - Move Servo 1 to position

    if (message[0] == 115 and message[1] == 49) { // s et 1
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      //servo1Pos = atoi(dataInS); // char to int

      //Serial.println(servo1Pos);
      //servo1Pos = map(servo1Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      //Serial.println(servo1Pos);
      //servo01.writeMicroseconds(1500); // 1000 a 2000

      // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
      //if (servo1PPos > servo1Pos) {
      //for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
      //servo01.write(j);
      //delayMicroseconds(speedServo);    // defines the speed at which the servo rotates
      //}
      //} else  if (servo1PPos < servo1Pos) { // If previous position is smaller then current position
      // for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
      //servo01.write(j);
      // delayMicroseconds(speedServo);
      //}
      //}
      //servo1PPos = servo1Pos;   // set current position as previous position
    }

    // If button "SAVE" is pressed
    if (message[0] == 83 and message[1] == 65 and message[2] == 86 and message[3] == 69) { // SAVE
      //servo01SP[index] = servo1PPos;  // save position into the array
      // servo02SP[index] = servo2PPos;
      //servo03SP[index] = servo3PPos;
      //servo04SP[index] = servo4PPos;
      //servo05SP[index] = servo5PPos;
      //servo06SP[index] = servo6PPos;
      //index++;                        // Increase the array index
    }
    if (message[0] == 82 and message[1] == 85 and message[2] == 78 ) { // RUN
      //runservo();  // Automatic mode - run the saved steps
    }
    // If button "RESET" is pressed
    if (message[0] == 82 and message[1] == 69 and message[2] == 83 and message[3] == 69 and message[4] == 84) { // RESET
      //memset(servo01SP, 0, sizeof(servo01SP)); // Clear the array data to 0
      //memset(servo02SP, 0, sizeof(servo02SP));
      //memset(servo03SP, 0, sizeof(servo03SP));
      //memset(servo04SP, 0, sizeof(servo04SP));
      //memset(servo05SP, 0, sizeof(servo05SP));
      //memset(servo06SP, 0, sizeof(servo06SP));
      //index = 0;  // Index to 0
    }
  }
}
#endif

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
  Wire.onReceive(fonctionI2C);
#endif
}

//=====
// loop
//=====
void loop() {
  // test avant creneau
  if (SensorIr() == 1 and sensorIRapres == 0 and sensorIRpendant == 0) {
    sensorIRavant = 1;  // 1  0  0
    sensorIRpendant = 0;
    sensorIRapres = 0;
    Serial.println("avant");
    //test pendant creneau
  } else if (SensorIr() == 0) {
    sensorIRpendant = 1; // 1  1  0
    sensorIRavant = 1;
    sensorIRapres = 0;
    Serial.println("pendant");
    //test apres creneau
  } else if (SensorIr() == 1 and sensorIRavant == 1 ) {
    sensorIRapres = 1;  //  0  0  1
    sensorIRavant = 0;
    sensorIRpendant = 0;
    Serial.println("apres");
    digitalWrite(ledsBlanches, LOW); // leds blanches pour le detecteur de couleur
    delay(300);
    getFrequency(); // test les differentes couleurs
    checkColor();  // selectionne la bonne couleur
    delay(300);
    digitalWrite(ledsBlanches, HIGH); // leds blanches pour le detecteur de couleur
  }


#if I2C and !TEST
  fonctionI2C();
#endif

}
