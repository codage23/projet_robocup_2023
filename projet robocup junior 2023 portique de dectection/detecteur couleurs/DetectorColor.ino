#include <Servo.h>

int ledRed = A0;
int ledYellow = A1;
int ledBlue = A2;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int pinServo1 = 9;
int pinServo2 = 10;
int pinServo3 = 11;
int pinServo4 = 12;
int pinServo5 = 13;

int posStartServo1 = 50;
int posEndServo1 = 90;

int posStartServo2 = 25;
int posEndServo2 = 0;

int posStartServo3 = 70;
int posEndServo3 = 120;

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequencyRed = 0;
int frequencyGreen = 0;
int frequencyBlue = 0;

bool colorFind = false;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);

  moveServoStart();

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}
void loop() {
  getFrequency();

  if (!colorFind) {
    checkColor();
  } else {
    moveBlock();
  }
}

void getFrequency() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequencyRed = pulseIn(sensorOut, LOW);
  Serial.print("Rouge = ");
  Serial.print(frequencyRed);
  Serial.print("  ");

  
  delay(100);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequencyGreen = pulseIn(sensorOut, LOW);
  Serial.print("Verte= ");
  Serial.print(frequencyGreen);
  Serial.print("  ");

  
  delay(100);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequencyBlue = pulseIn(sensorOut, LOW);
  Serial.print("Bleu= ");
  Serial.print(frequencyBlue);
  Serial.println("  ");
  delay(100);
}

void checkColor() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, LOW);
  if ((frequencyRed < 45 && frequencyRed > 25)
      && (frequencyGreen < 105 && frequencyGreen > 85)
      && (frequencyBlue < 75 && frequencyBlue > 55)) {
    digitalWrite(ledRed, HIGH);
    colorFind = true;
  } else if ((frequencyRed < 45 && frequencyRed > 25)
             && (frequencyGreen < 60 && frequencyGreen > 40)
             && (frequencyBlue < 85 && frequencyBlue > 65)) {
    digitalWrite(ledYellow, HIGH);
    colorFind = true;
  } else if ((frequencyRed < 90 && frequencyRed > 70)
             && (frequencyGreen < 95 && frequencyGreen > 75)
             && (frequencyBlue < 60 && frequencyBlue > 40)) {
    digitalWrite(ledBlue, HIGH);
    colorFind = true;
  }
}

void moveServoStart() {
  servo1.write(posStartServo1);
  servo2.write(posStartServo2);
  servo3.write(posStartServo3);
  servo4.write(90);
  servo5.write(90);
}

void moveBlock() {
  clawClose();

  setServoPosition(servo2, posStartServo2, posEndServo2);
  setServoPosition(servo3, posStartServo3, posEndServo3);

  setServoPosition(servo1, posStartServo1, posEndServo1);

  setServoPosition(servo1, posEndServo1, posStartServo1);
  setServoPosition(servo3, posEndServo3, posStartServo3);
  setServoPosition(servo2, posEndServo2, posStartServo2);

  delay(2000);

  clawOpen();

  moveServoStart();

  colorFind = false;
}

void setServoPosition(Servo servo, int startPosition, int endPosition) {
  if (startPosition > endPosition) {
    for (int i = startPosition; i >= endPosition; i--) {
      servo.write(i);
      delay(30);
    }
  } else {
    for (int i = startPosition; i <= endPosition; i++) {
      servo.write(i);
      delay(30);
    }
  }
}

void clawOpen() {
  servo4.write(70);
  servo5.write(100);
}

void clawClose() {
  servo4.write(100);
  servo5.write(80);

}
