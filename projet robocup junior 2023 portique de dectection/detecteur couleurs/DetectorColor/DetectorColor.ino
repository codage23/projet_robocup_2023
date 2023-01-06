
int ledRed = 9;
int ledGreen = 11;
int ledBlue = 10;
int ledRed1 = 7;
int ledGreen1 = 12;
int ledBlue1 = 8;

#define ledsBlanches A0


#define S0 6
#define S1 5
#define S2 4
#define S3 3
#define sensorOut 2

int frequencyRed = 0;
int frequencyGreen = 0;
int frequencyBlue = 0;

int red_value = 0;
int green_value = 0;
int blue_value = 0;

bool colorFind = false;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Demarrage du detecteur de couleurs");

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed1, OUTPUT);
  pinMode(ledGreen1, OUTPUT);
  pinMode(ledBlue1, OUTPUT);
  pinMode(ledsBlanches, OUTPUT);

  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledRed1, LOW);
  digitalWrite(ledGreen1, LOW);
  digitalWrite(ledBlue1, LOW);
  digitalWrite(ledsBlanches, HIGH);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  digitalWrite(ledsBlanches, LOW); // leds blanches pour le detecteur de couleur

  getFrequency();
  checkColor();
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

void checkColor() {

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
    digitalWrite(ledRed1, HIGH);
    digitalWrite(ledGreen1, LOW);
    digitalWrite(ledBlue1, LOW);

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
    digitalWrite(ledRed1, LOW);
    digitalWrite(ledGreen1, HIGH);
    digitalWrite(ledBlue1, LOW);

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
    digitalWrite(ledRed1, LOW);
    digitalWrite(ledGreen1, LOW);
    digitalWrite(ledBlue1, HIGH);

  } else {
    Serial.println(" no detected!");
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledRed1, LOW);
    digitalWrite(ledGreen1, LOW);
    digitalWrite(ledBlue1, LOW);
  }
  /*
    // if ((frequencyRed < 45 && frequencyRed > 25)  && (frequencyGreen < 105 && frequencyGreen > 85)
    //     && (frequencyBlue < 75 && frequencyBlue > 55)) {
    if (((frequencyRed < 50 + 20) && (frequencyRed > 50 - 20 ))
        && ((frequencyGreen < 90 + 20) && (frequencyGreen > 90 - 20))
        && ((frequencyBlue < 70 + 20) && (frequencyBlue > 70 - 20))) {
      digitalWrite(ledRed, HIGH);
      colorFind = true;
    } else if (((frequencyRed < 90 + 20) && (frequencyRed > 90 - 20 ))
               && ((frequencyGreen < 70 + 20) && (frequencyGreen > 70 - 20))
               && ((frequencyBlue < 80 + 20) && (frequencyBlue > 80 - 20))) {
      digitalWrite(ledGreen, HIGH);
      colorFind = true;
    } else if (((frequencyRed < 90 + 20) && (frequencyRed > 90 - 20 ))
               && ((frequencyGreen < 80 + 20) && (frequencyGreen > 80 - 20))
               && ((frequencyBlue < 50 + 20) && (frequencyBlue > 50 - 20))) {
      digitalWrite(ledBlue, HIGH);
      colorFind = true;
    } else {
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledBlue, LOW);
    }
  */
}
