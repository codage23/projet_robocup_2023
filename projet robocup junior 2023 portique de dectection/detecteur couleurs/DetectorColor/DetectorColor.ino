
int ledRed = 9;
int ledGreen = 11;
int ledBlue = 10;


#define S0 6
#define S1 5
#define S2 4
#define S3 3
#define sensorOut 2
int frequencyRed = 0;
int frequencyGreen = 0;
int frequencyBlue = 0;

bool colorFind = false;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Demarrage du detecteur de couleurs");


  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  getFrequency();

 // if (!colorFind) {
    checkColor();
 // } else {

 /// }
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

  // if ((frequencyRed < 45 && frequencyRed > 25)  && (frequencyGreen < 105 && frequencyGreen > 85)
  //     && (frequencyBlue < 75 && frequencyBlue > 55)) {
  if ((frequencyRed < 1300 && frequencyRed > 800)  && (frequencyGreen < 2900 && frequencyGreen > 1700)
      && (frequencyBlue < 2800 && frequencyBlue > 1700)) {
    digitalWrite(ledRed, HIGH);
    colorFind = true;
  } else if ((frequencyRed < 1700 && frequencyRed > 1200)
             && (frequencyGreen < 2100 && frequencyGreen > 1500)
             && (frequencyBlue < 1900 && frequencyBlue > 1500)) {
    digitalWrite(ledGreen, HIGH);
    colorFind = true;
  } else if ((frequencyRed < 90 && frequencyRed > 70)
             && (frequencyGreen < 95 && frequencyGreen > 75)
             && (frequencyBlue < 60 && frequencyBlue > 40)) {
    digitalWrite(ledBlue, HIGH);
    colorFind = true;
  } else {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
  }
}

/*
/============
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
=============/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(100);
}

/===============
  Complete project details at https://randomnerdtutorials.com  
==================/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // redColor = map(redFrequency, 70, 120, 255,0);
  redColor = map(redFrequency, XX, XX, 255,0);
  
  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = map(greenFrequency, XX, XX, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = map(blueFrequency, XX, XX, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);

  // Checks the current detected color and prints
  // a message in the serial monitor
  if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - RED detected!");
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - GREEN detected!");
  }
  if(blueColor > redColor && blueColor > greenColor){
    Serial.println(" - BLUE detected!");
  }
}
 */
