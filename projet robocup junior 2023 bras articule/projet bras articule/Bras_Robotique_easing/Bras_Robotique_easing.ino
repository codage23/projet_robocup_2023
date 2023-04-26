/***********************************************
       DIY Arduino Robot Arm Smartphone Control
        by Dejan, www.HowToMechatronics.com

        jlm dec 2022
************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <SoftwareSerial.h>
#include <Servo.h>
#include <ServoEasing.hpp>
#include <Wire.h> //composants utilisant le protocole I2C
#include "variables.h"

//================
// objet bluetooth
//================
#if BLUETOOTH and !TEST and !I2C
SoftwareSerial Bluetooth(3, 4); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
#endif

//==============
// objets servxx
//==============
/*
  Servo servo01; // waist
  Servo servo02; // shoulder
  Servo servo03; // elbow
  Servo servo04; // wrist roll
  Servo servo05; // wrist pitch
  Servo servo06; // gripper
*/
ServoEasing servo01; // waist
ServoEasing servo02; // shoulder
ServoEasing servo03; // elbow
ServoEasing servo04; // wrist roll
ServoEasing servo05; // wrist pitch
ServoEasing servo06; // gripper

//=======
// setup
//=======
void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println();
  Serial.println("Demarrage du bras articule");

  servo01.attach(WAIST);
  servo01.setSpeed(speedServo);      // speedServo degree per second blocking
  //  Servo1.setEasingType(EASE_CUBIC_IN_OUT); // EASE_LINEAR is default
  servo01.setEasingType(EASE_SINE_IN_OUT);  // sinus
  servo1PPos = PP_WAIST;     // Robot arm initial position
  servo01.easeTo(servo1PPos);

  servo02.attach(SHOULDER);
  servo02.setSpeed(speedServo);      // speedServo degree per second blocking
  servo02.setEasingType(EASE_SINE_IN_OUT);  // sinus
  servo2PPos = PP_SHOULDER;  // Robot arm initial position
  servo02.easeTo(servo2PPos);

  servo03.attach(ELBOW);
  servo03.setSpeed(speedServo);      // speedServo degree per second blocking
  servo03.setEasingType(EASE_SINE_IN_OUT);  // sinus
  servo3PPos = PP_ELBOW;     // Robot arm initial position
  servo03.easeTo(servo3PPos);

  servo04.attach(WRIST_ROLL);
  servo04.setSpeed(speedServo);       // speedServo degree per second blocking
  servo04.setEasingType(EASE_SINE_IN_OUT);  // sinus
  servo4PPos = PP_WRIST_ROLL; // Robot arm initial position
  servo04.easeTo(servo4PPos);

  servo05.attach(WRIST_PITCH);
  servo05.setSpeed(speedServo);       // speedServo degree per second blocking
  servo05.setEasingType(EASE_SINE_IN_OUT);  // sinus
  servo5PPos = PP_WRIST_PITCH;// Robot arm initial position
  servo05.easeTo(servo5PPos);

  servo06.attach(GRIPPER);
  servo06.setSpeed(speedServo);       // speedServo degree per second blocking
  servo06.setEasingType(EASE_SINE_IN_OUT);  // sinus
  servo6PPos = PP_GRIPPER;    // Robot arm initial position
  servo06.easeTo(servo6PPos);

#if BLUETOOTH and !TEST and !I2C
  Bluetooth.begin(SERIAL_BAUD_BLUETOOTH); // SoftwareSerial
  //Bluetooth.setTimeout(1);
  delay(20);
#endif
#if I2C and !TEST and !BLUETOOTH
  // Initialise la library Wire et se connecte au bus I2C en tant qu'esclave
  Wire.begin(I2C_SLAVE_BRAS);
  // Définition de la fonction qui prendra en charge les informations recues sur le bus I2C
  Wire.onReceive(fonctionI2C);
#endif
}

//=====
// loop
//=====
void loop() {

#if I2C and !TEST
  fonctionI2C();
#endif

#if TEST and !I2C
  fonctionTest();
#endif

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
    int taille = strlen(message); // taille de la chaine
    Serial.print("taille du message : ");
    Serial.println(taille);
    char dataInS[taille];

    // If "Waist" slider has changed value - Move Servo 1 to position
    if (message[0] == 115 and message[1] == 49) {            // s et 1
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      servo1Pos = atoi(dataInS); // char to int
      Serial.print("servo 1 position : ");
      servo1Pos = map(servo1Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo1Pos);
      servo01.easeTo(servo1Pos);
      servo1PPos = servo1Pos;   // set current position as previous position
    }

    // Move Servo 2  shoulder
    if (message[0] == 115 and message[1] == 50) { // s et 2
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      servo2Pos = atoi(dataInS); // char to int
      Serial.print("servo 2 position : ");
      servo2Pos = map(servo2Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo2Pos);
      servo02.easeTo(servo2Pos);
      servo2PPos = servo2Pos;
    }

    // Move Servo 3  elbow
    if (message[0] == 115 and message[1] == 51) { // s et 3
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      servo3Pos = atoi(dataInS); // char to int
      Serial.print("servo 3 position : ");
      servo3Pos = map(servo3Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo3Pos);
      servo03.easeTo(servo3Pos);
      servo3PPos = servo3Pos;
    }

    // Move Servo 4  wrist roll
    if (message[0] == 115 and message[1] == 52) { // s et 4
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      servo4Pos = atoi(dataInS); // char to int
      Serial.print("servo 4 position : ");
      servo4Pos = map(servo4Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo4Pos);
      servo04.easeTo(servo4Pos);
      servo4PPos = servo4Pos;
    }

    // Move Servo 5  wrist pitch
    if (message[0] == 115 and message[1] == 53) { // s et 5
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      servo5Pos = atoi(dataInS); // char to int
      Serial.print("servo 5 position : ");
      servo5Pos = map(servo5Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo5Pos);
      servo05.easeTo(servo5Pos);
      servo5PPos = servo5Pos;
    }

    // Move Servo 6  gripper
    if (message[0] == 115 and message[1] == 54) { // s et 6
      // Extract only the number. E.g. from "s1120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      servo6Pos = atoi(dataInS); // char to int
      Serial.print("servo 6 position : ");
      servo6Pos = map(servo6Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo6Pos);
      servo06.easeTo(servo6Pos);
      servo6PPos = servo6Pos;
    }

    // If button "SAVE" is pressed
    if (message[0] == 83 and message[1] == 65 and message[2] == 86 and message[3] == 69) { // SAVE
      servo01SP[index] = servo1PPos;  // save position into the array
      servo02SP[index] = servo2PPos;
      servo03SP[index] = servo3PPos;
      servo04SP[index] = servo4PPos;
      servo05SP[index] = servo5PPos;
      servo06SP[index] = servo6PPos;
      index++;                        // Increase the array index
    }

    // If button "RESET" is pressed
    if (message[0] == 82 and message[1] == 69 and message[2] == 83 and message[3] == 69 and message[4] == 84) { // RESET
      servo1PPos = PP_WAIST;        // Robot arm initial position
      servo01.easeTo(servo1PPos);
      servo2PPos = PP_SHOULDER;     // Robot arm initial position
      servo02.easeTo(servo2PPos);
      servo3PPos = PP_ELBOW;        // Robot arm initial position
      servo03.easeTo(servo3PPos);
      servo4PPos = PP_WRIST_ROLL;   // Robot arm initial position
      servo04.easeTo(servo4PPos);
      servo5PPos = PP_WRIST_PITCH;  // Robot arm initial position
      servo05.easeTo(servo5PPos);
      servo6PPos = PP_GRIPPER;      // Robot arm initial position
      servo06.easeTo(servo6PPos);
      index = 0;  // Index to 0
    }
  }
}
#endif

#if TEST and !I2C
void fonctionTest() {
  //tourTestServo06(48, 150); // test du servo06 gripper
  //tourTestServo05(40, 120); // test du servo05 wrist pitch
  //tourTestServo04(80, 170); // test du servo04 wrist roll
  //tourTestServo03(30, 150); // test du servo03 elbow
  //tourTestServo02(60, 160); // test du servo02 shoulder
  //tourTestServo01(00, 180); // test du servo01 waist
}

void tourTestServo06(int min, int max) {
  delay(300);
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo06.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo06.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  servo6PPos = PP_GRIPPER;
  servo06.easeTo(servo6PPos);
  delay(2000);
}

void tourTestServo05(int min, int max) {
  delay(300);
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo05.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo05.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  servo5PPos = PP_WRIST_PITCH;
  servo05.easeTo(servo5PPos);
  delay(2000);
}

void tourTestServo04(int min, int max) {
  delay(300);
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo04.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo04.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  servo4PPos = PP_WRIST_ROLL;
  servo04.easeTo(servo4PPos);
  delay(2000);
}

void tourTestServo03(int min, int max) {
  delay(300);
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo03.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo03.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  servo3PPos = PP_ELBOW ;
  servo03.easeTo(servo3PPos);
  delay(2000);
}

void tourTestServo02(int min, int max) {
  delay(300);
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo02.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(300);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo02.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  servo2PPos = PP_SHOULDER;
  servo02.easeTo(servo4PPos);
  delay(2000);
}

void tourTestServo01(int min, int max) {
  delay(300);
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo01.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo01.easeTo(i);
    Serial.print("Angle:  ");
    Serial.println(i);
  }
  delay(300);
  servo1PPos = PP_WAIST;
  servo01.easeTo(servo1PPos);
  delay(2000);
}
#endif
