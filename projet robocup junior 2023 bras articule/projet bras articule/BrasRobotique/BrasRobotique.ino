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
Servo servo01; // waist
Servo servo02; // shoulder
Servo servo03; // elbow
Servo servo04; // wrist roll
Servo servo05; // wrist pitch
Servo servo06; // gripper

//=======
// setup
//=======
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Demarrage du bras articule");

  servo01.attach(WAIST);
  servo1PPos = PP_WAIST;  // Robot arm initial position
  servo01.write(servo1PPos);

  servo02.attach(SHOULDER);
  servo2PPos = PP_SHOULDER; // Robot arm initial position
  servo02.write(servo2PPos);

  servo03.attach(ELBOW);
  servo3PPos = PP_ELBOW; // Robot arm initial position
  servo03.write(servo3PPos);

  servo04.attach(WRIST_ROLL);
  servo4PPos = PP_WRIST_ROLL; // Robot arm initial position
  servo04.write(servo4PPos);

  servo05.attach(WRIST_PITCH);
  servo5PPos = PP_WRIST_PITCH;// Robot arm initial position
  servo05.write(servo5PPos);

  servo06.attach(GRIPPER);
  servo6PPos = PP_GRIPPER;// Robot arm initial position
  servo06.write(servo6PPos);

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

#if I2C and !BLUETOOTH and !TEST
  fonctionI2C();
#endif

#if TEST and !BLUETOOTH and !I2C
  fonctionTest();
#endif

#if BLUETOOTH and !TEST and !I2C
  fonctionBluetooth();
#endif

}

#if I2C and !BLUETOOTH and !TEST
void fonctionI2C() {
  // Check for incoming data
  // Lecture du module I2C et affichage des donnees sur le moniteur serie de l'Ordinateur
  if (Wire.available() > 0) {
    // *******   dataIn = I2C.readString();  // Read the data as string
    dataIn = 90;
    Serial.println(dataIn);

    // If "Waist" slider has changed value - Move Servo 1 to position
    if (dataIn.startsWith("s1")) {
      // Extract only the number. E.g. from "s1120" to "120"
      String dataInS = dataIn.substring(2, dataIn.length());
      servo1Pos = dataInS.toInt();  // Convert the string into integer
      Serial.println(servo1Pos);
      servo1Pos = map(servo1Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo1Pos);

      // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
          servo01.write(j);
          delay(20);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
          servo01.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;   // set current position as previous position
    }

    // Move Servo 2  shoulder
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo2Pos = dataInS.toInt();
      Serial.println(servo2Pos);
      servo2Pos = map(servo2Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo2Pos);

      if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          delay(50);
        }
      }
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          delay(50);
        }
      }
      servo2PPos = servo2Pos;
    }
    // Move Servo 3  elbow
    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo3Pos = dataInS.toInt();
      Serial.println(servo3Pos);
      servo3Pos = map(servo3Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo3Pos);

      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(30);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(30);
        }
      }
      servo3PPos = servo3Pos;
    }
    // Move Servo 4  wrist roll
    if (dataIn.startsWith("s4")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo4Pos = dataInS.toInt();
      Serial.println(servo4Pos);
      servo4Pos = map(servo4Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo4Pos);

      if (servo4PPos > servo4Pos) {
        for ( int j = servo4PPos; j >= servo4Pos; j--) {
          servo04.write(j);
          delay(30);
        }
      }
      if (servo4PPos < servo4Pos) {
        for ( int j = servo4PPos; j <= servo4Pos; j++) {
          servo04.write(j);
          delay(30);
        }
      }
      servo4PPos = servo4Pos;
    }
    // Move Servo 5  wrist pitch
    if (dataIn.startsWith("s5")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo5Pos = dataInS.toInt();
      Serial.println(servo5Pos);
      servo5Pos = map(servo5Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo5Pos);

      if (servo5PPos > servo5Pos) {
        for ( int j = servo5PPos; j >= servo5Pos; j--) {
          servo05.write(j);
          delay(30);
        }
      }
      if (servo5PPos < servo5Pos) {
        for ( int j = servo5PPos; j <= servo5Pos; j++) {
          servo05.write(j);
          delay(30);
        }
      }
      servo5PPos = servo5Pos;
    }
    // Move Servo 6  gripper
    if (dataIn.startsWith("s6")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo6Pos = dataInS.toInt();
      Serial.println(servo6Pos);
      servo6Pos = map(servo6Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo6Pos);

      if (servo6PPos > servo6Pos) {
        for ( int j = servo6PPos; j >= servo6Pos; j--) {
          servo06.write(j);
          delay(30);
        }
      }
      if (servo6PPos < servo6Pos) {
        for ( int j = servo6PPos; j <= servo6Pos; j++) {
          servo06.write(j);
          delay(30);
        }
      }
      servo6PPos = servo6Pos;
    }
    // If button "SAVE" is pressed
    if (dataIn.startsWith("SAVE")) {
      servo01SP[index] = servo1PPos;  // save position into the array
      servo02SP[index] = servo2PPos;
      servo03SP[index] = servo3PPos;
      servo04SP[index] = servo4PPos;
      servo05SP[index] = servo5PPos;
      servo06SP[index] = servo6PPos;
      index++;                        // Increase the array index
    }
    // If button "RUN" is pressed
    if (dataIn.startsWith("RUN")) {
      runservo();  // Automatic mode - run the saved steps
    }
    // If button "RESET" is pressed
    if ( dataIn == "RESET") {
      memset(servo01SP, 0, sizeof(servo01SP)); // Clear the array data to 0
      memset(servo02SP, 0, sizeof(servo02SP));
      memset(servo03SP, 0, sizeof(servo03SP));
      memset(servo04SP, 0, sizeof(servo04SP));
      memset(servo05SP, 0, sizeof(servo05SP));
      memset(servo06SP, 0, sizeof(servo06SP));
      index = 0;  // Index to 0
    }
  }
}

// Automatic mode custom function - run the saved steps
void runservo() {
  while (dataIn != "RESET") {   // Run the steps over and over again until "RESET" button is pressed
    for (int i = 0; i <= index - 2; i++) {  // Run through all steps(index)
      //*****        dataIn = I2C.readString();
      dataIn = 90;
      if ( dataIn == "PAUSE") {           // If button "PAUSE" is pressed
        while (dataIn != "RUN") {         // Wait until "RUN" is pressed again
          // ****             dataIn = I2C.readString();
          dataIn = 90;
          if ( dataIn == "RESET") {
            break;
          }
        }
      }
      // If speed slider is changed
      if (dataIn.startsWith("ss")) {
        String dataInS = dataIn.substring(2, dataIn.length());
        speedDelay = dataInS.toInt(); // Change servo speed (delay time)
        Serial.println(speedDelay);
      }
      // Servo 1
      if (servo01SP[i] == servo01SP[i + 1]) {
      }
      if (servo01SP[i] > servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }

      // Servo 2
      if (servo02SP[i] == servo02SP[i + 1]) {
      }
      if (servo02SP[i] > servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }

      // Servo 3
      if (servo03SP[i] == servo03SP[i + 1]) {
      }
      if (servo03SP[i] > servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }

      // Servo 4
      if (servo04SP[i] == servo04SP[i + 1]) {
      }
      if (servo04SP[i] > servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }

      // Servo 5
      if (servo05SP[i] == servo05SP[i + 1]) {
      }
      if (servo05SP[i] > servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j >= servo05SP[i + 1]; j--) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      if (servo05SP[i] < servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j <= servo05SP[i + 1]; j++) {
          servo05.write(j);
          delay(speedDelay);
        }
      }

      // Servo 6
      if (servo06SP[i] == servo06SP[i + 1]) {
      }
      if (servo06SP[i] > servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j >= servo06SP[i + 1]; j--) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
      if (servo06SP[i] < servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j <= servo06SP[i + 1]; j++) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}
#endif

#if TEST and !BLUETOOTH and !I2C
void fonctionTest() {
  //tourTestServo06(48, 150); // test du servo06 gripper
  //tourTestServo05(40, 120); // test du servo05 wrist pitch
  //tourTestServo04(80, 170); // test du servo04 wrist roll
  //tourTestServo03(30, 150); // test du servo03 elbow
  //tourTestServo02(90, 180); // test du servo02 shoulder
  //tourTestServo01(00, 180); // test du servo01 waist
}

void tourTestServo06(int min, int max) {
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo06.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo06.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  servo6PPos = PP_GRIPPER;
  servo06.write(servo6PPos);
  delay(1000);
}

void tourTestServo05(int min, int max) {
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo05.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo05.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  servo5PPos = PP_WRIST_PITCH;
  servo05.write(servo5PPos);
  delay(1000);
}

void tourTestServo04(int min, int max) {
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo04.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo04.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  servo4PPos = PP_WRIST_ROLL;
  servo04.write(servo4PPos);
  delay(1000);
}

void tourTestServo03(int min, int max) {
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo03.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo03.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  servo3PPos = PP_ELBOW ;
  servo03.write(servo3PPos);
  delay(1000);
}

void tourTestServo02(int min, int max) {
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo02.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo02.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  servo2PPos = PP_SHOULDER;
  servo02.write(servo4PPos);
  delay(1000);
}

void tourTestServo01(int min, int max) {
  // tour max de 0 à 180º
  for (int i = min; i <= max; i++) {
    servo01.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  // tour max de 180 a 0º
  for (int i = max; i > min; i--) {
    servo01.write(i);
    Serial.print("Angle:  ");
    Serial.println(i);
    delay(100);
  }
  delay(1000);
  servo1PPos = PP_WAIST;
  servo01.write(servo1PPos);
  delay(1000);
}
#endif

#if BLUETOOTH and !TEST and !I2C
void fonctionBluetooth () {
  // Check for incoming data
  if (Bluetooth.available() > 0) {
    // Lecture du module BT et affichage des donnees sur le moniteur serie de l'Ordinateur
    dataIn = Bluetooth.readString();  // Read the data as string
    Serial.println(dataIn);

    // If "Waist" slider has changed value - Move Servo 1 to position
    if (dataIn.startsWith("s1")) {
      // Extract only the number. E.g. from "s1120" to "120"
      String dataInS = dataIn.substring(2, dataIn.length());
      servo1Pos = dataInS.toInt();  // Convert the string into integer
      Serial.println(servo1Pos);
      servo1Pos = map(servo1Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo1Pos);

      // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
          servo01.write(j);
          delay(20);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
          servo01.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;   // set current position as previous position
    }

    // Move Servo 2  shoulder
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo2Pos = dataInS.toInt();
      Serial.println(servo2Pos);
      servo2Pos = map(servo2Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo2Pos);

      if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          delay(50);
        }
      }
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          delay(50);
        }
      }
      servo2PPos = servo2Pos;
    }
    // Move Servo 3  elbow
    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo3Pos = dataInS.toInt();
      Serial.println(servo3Pos);
      servo3Pos = map(servo3Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo3Pos);

      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(30);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(30);
        }
      }
      servo3PPos = servo3Pos;
    }
    // Move Servo 4  wrist roll
    if (dataIn.startsWith("s4")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo4Pos = dataInS.toInt();
      Serial.println(servo4Pos);
      servo4Pos = map(servo4Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo4Pos);

      if (servo4PPos > servo4Pos) {
        for ( int j = servo4PPos; j >= servo4Pos; j--) {
          servo04.write(j);
          delay(30);
        }
      }
      if (servo4PPos < servo4Pos) {
        for ( int j = servo4PPos; j <= servo4Pos; j++) {
          servo04.write(j);
          delay(30);
        }
      }
      servo4PPos = servo4Pos;
    }
    // Move Servo 5  wrist pitch
    if (dataIn.startsWith("s5")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo5Pos = dataInS.toInt();
      Serial.println(servo5Pos);
      servo5Pos = map(servo5Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo5Pos);

      if (servo5PPos > servo5Pos) {
        for ( int j = servo5PPos; j >= servo5Pos; j--) {
          servo05.write(j);
          delay(30);
        }
      }
      if (servo5PPos < servo5Pos) {
        for ( int j = servo5PPos; j <= servo5Pos; j++) {
          servo05.write(j);
          delay(30);
        }
      }
      servo5PPos = servo5Pos;
    }
    // Move Servo 6  gripper
    if (dataIn.startsWith("s6")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo6Pos = dataInS.toInt();
      Serial.println(servo6Pos);
      servo6Pos = map(servo6Pos, 0, 180, 0, 180); //utilisation de map pour limiter l'ouverture du servo
      Serial.println(servo6Pos);

      if (servo6PPos > servo6Pos) {
        for ( int j = servo6PPos; j >= servo6Pos; j--) {
          servo06.write(j);
          delay(30);
        }
      }
      if (servo6PPos < servo6Pos) {
        for ( int j = servo6PPos; j <= servo6Pos; j++) {
          servo06.write(j);
          delay(30);
        }
      }
      servo6PPos = servo6Pos;
    }
    // If button "SAVE" is pressed
    if (dataIn.startsWith("SAVE")) {
      servo01SP[index] = servo1PPos;  // save position into the array
      servo02SP[index] = servo2PPos;
      servo03SP[index] = servo3PPos;
      servo04SP[index] = servo4PPos;
      servo05SP[index] = servo5PPos;
      servo06SP[index] = servo6PPos;
      index++;                        // Increase the array index
    }
    // If button "RUN" is pressed
    if (dataIn.startsWith("RUN")) {
      runservo();  // Automatic mode - run the saved steps
    }
    // If button "RESET" is pressed
    if ( dataIn == "RESET") {
      memset(servo01SP, 0, sizeof(servo01SP)); // Clear the array data to 0
      memset(servo02SP, 0, sizeof(servo02SP));
      memset(servo03SP, 0, sizeof(servo03SP));
      memset(servo04SP, 0, sizeof(servo04SP));
      memset(servo05SP, 0, sizeof(servo05SP));
      memset(servo06SP, 0, sizeof(servo06SP));
      index = 0;  // Index to 0
    }
  }
}

// Automatic mode custom function - run the saved steps
void runservo() {
  while (dataIn != "RESET") {   // Run the steps over and over again until "RESET" button is pressed
    for (int i = 0; i <= index - 2; i++) {  // Run through all steps(index)
      if (Bluetooth.available() > 0) {      // Check for incomding data
        dataIn = Bluetooth.readString();
        if ( dataIn == "PAUSE") {           // If button "PAUSE" is pressed
          while (dataIn != "RUN") {         // Wait until "RUN" is pressed again
            if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.readString();
              if ( dataIn == "RESET") {
                break;
              }
            }
          }
        }
        // If speed slider is changed
        if (dataIn.startsWith("ss")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          speedDelay = dataInS.toInt(); // Change servo speed (delay time)
          Serial.println(speedDelay);
        }
      }
      // Servo 1
      if (servo01SP[i] == servo01SP[i + 1]) {
      }
      if (servo01SP[i] > servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }

      // Servo 2
      if (servo02SP[i] == servo02SP[i + 1]) {
      }
      if (servo02SP[i] > servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }

      // Servo 3
      if (servo03SP[i] == servo03SP[i + 1]) {
      }
      if (servo03SP[i] > servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }

      // Servo 4
      if (servo04SP[i] == servo04SP[i + 1]) {
      }
      if (servo04SP[i] > servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }

      // Servo 5
      if (servo05SP[i] == servo05SP[i + 1]) {
      }
      if (servo05SP[i] > servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j >= servo05SP[i + 1]; j--) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      if (servo05SP[i] < servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j <= servo05SP[i + 1]; j++) {
          servo05.write(j);
          delay(speedDelay);
        }
      }

      // Servo 6
      if (servo06SP[i] == servo06SP[i + 1]) {
      }
      if (servo06SP[i] > servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j >= servo06SP[i + 1]; j--) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
      if (servo06SP[i] < servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j <= servo06SP[i + 1]; j++) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}
#endif
