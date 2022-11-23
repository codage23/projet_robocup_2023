#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int pinServo1 = 2;
int pinServo2 = 3;
int pinServo3 = 4;
int pinServo4 = 5;
int pinServo5 = 6;

int leftButton = 7;
int rightButton = 8;

int potentiometer1 = A0;
int potentiometer2 = A1;
int potentiometer3 = A2;

//Record section
int buttonStartRecord = 9;
int buttonStopRecord = 10;
int buttonPlayRecord = 11;
int ledStopRecord = 12;
int ledStartRecord = 13;

bool isRecord = false;
bool isPlay = false;
int indexRecord = 0;

const int moveCount = 10;
const int servoNumber = 4;
int movesServos[moveCount][servoNumber]; //max of 10 moves


Servo servos[servoNumber] = {servo1, servo2, servo3, servo4};
//END Record section

void setup() {
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);

  clawOpen();

  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);

  //Record section
  pinMode(buttonStartRecord, INPUT);
  pinMode(buttonStopRecord, INPUT);
  pinMode(buttonPlayRecord, INPUT);

  pinMode(ledStartRecord, OUTPUT);
  pinMode(ledStopRecord, OUTPUT);
  //END Region section
  
  Serial.begin(9600);
}

void loop() {
  if (!isPlay) {
    int valPotentiometer1 = analogRead(potentiometer1);
    int valPotentiometer2 = analogRead(potentiometer2);
    int valPotentiometer3 = analogRead(potentiometer3);

    int valServo1 = map(valPotentiometer1, 0, 1023, 10, 170);
    int valServo2 = map(valPotentiometer2, 0, 1023, 10, 170);
    int valServo3 = map(valPotentiometer3, 0, 1023, 10, 170);

    servo1.write(valServo1);
    servo2.write(valServo2);
    servo3.write(valServo3);

    int leftButtonState = digitalRead(leftButton);
    int rightButtonState = digitalRead(rightButton);

    if (leftButtonState == HIGH && rightButtonState == HIGH) {
      clawOpen();
    } else {
      if (leftButtonState == HIGH) {
        clawOpen();
      }
      if (rightButtonState == HIGH) {
        clawClose();
      }
    }
  }
  
  record();

  delay(5);
}




void record() {
  int buttonStartRecordState =  digitalRead(buttonStartRecord);
  int buttonRecordMoveState =  digitalRead(buttonStopRecord);
  int buttonPlayRecordState =  digitalRead(buttonPlayRecord);

  if (buttonStartRecordState == HIGH) {
    if (!isRecord) {
      isRecord = true;
      digitalWrite(ledStopRecord, LOW);
      digitalWrite(ledStartRecord, HIGH);
      Serial.println("----START Record----");
      indexRecord = 0;
      memset(movesServos, 0, sizeof(movesServos));
    } else {
      isRecord = false;
      digitalWrite(ledStopRecord, LOW);
      digitalWrite(ledStartRecord, LOW);
    }
    delay(300);
  }

  if (buttonRecordMoveState == HIGH && isRecord) {
    digitalWrite(ledStopRecord, LOW);
    digitalWrite(ledStartRecord, LOW);
    recordMove();
    delay(300);
    digitalWrite(ledStopRecord, LOW);
    digitalWrite(ledStartRecord, HIGH);

  } else if (buttonRecordMoveState == HIGH && isPlay) {
    isPlay = false;
    digitalWrite(ledStopRecord, LOW);
    digitalWrite(ledStartRecord, LOW);
  }
  if (buttonPlayRecordState == HIGH) {

    digitalWrite(ledStopRecord, HIGH);
    digitalWrite(ledStartRecord, LOW);
    isPlay = true;
  }

  if (isPlay) {
    Serial.println("Play");
    playRecord();

    delay(300);
  }
}

void recordMove() {
  if (indexRecord < moveCount) {
    int servoRead1 =  servo1.read();
    int servoRead2 =  servo2.read();
    int servoRead3 =  servo3.read();
    int servoRead4 =  servo4.read();
    int servoRead5 =  servo5.read();

    movesServos[indexRecord][0] = servoRead1;
    movesServos[indexRecord][1] = servoRead2;
    movesServos[indexRecord][2] = servoRead3;

    int servo3Value;
    if (servo4.read() == 100 && servo5.read() == 80) {
      servo3Value = 1;
    } else {
      servo3Value = 0;
    }

    movesServos[indexRecord][3] = servo3Value;

    indexRecord++;
  } else {
    Serial.println("Max array");
  }

}

void playRecord() {
  moves();
  goToStartPosition();

  delay(1000);
}

void moves() {
  for ( int i = 0; i < indexRecord - 1; i++) {
    for ( int j = 0; j < servoNumber; ++j ) {
      if (j >= 3) {
        if (movesServos[i + 1][j] == 1) {
          clawOpen();
        } else {
          clawClose();
        }
      } else {
        setServoPosition(servos[j], movesServos[i][j], movesServos[i + 1][j]);
      }
    }
  }
}

void goToStartPosition() {

  for ( int j = 0; j < servoNumber; ++j ) {
      if (j >= 3) {
        if (movesServos[0][j] == 1) {
          clawOpen();
        } else {
          clawClose();
        }
      } else {
        setServoPosition(servos[j], servos[j].read(), movesServos[0][j]);
      }
    }
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
  servo4.write(100);
  servo5.write(80);
}

void clawClose() {
  servo4.write(20);
  servo5.write(160);
}
