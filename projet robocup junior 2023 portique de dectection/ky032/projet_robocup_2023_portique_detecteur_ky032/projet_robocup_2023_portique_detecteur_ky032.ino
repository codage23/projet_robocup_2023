/*
* projet robocup 2023
* test detecteur KY032
*/
int Sensor = 13;  // Declaration of the sensor input pin

void setup() {
  Serial.begin(9600);      // Initialization serial output
  pinMode(Sensor, INPUT);  // Initialization of sensor pin
}
// The program reads the current status of the sensor pin and
// displays in the serial console whether an obstacle is currently detected
// or if there is no obstacle in front of the sensor
void loop() {
  // The current signal at the sensor is read out
  bool val = digitalRead(Sensor);
  // If a signal could be detected, the LED is switched on.
  if (val == HIGH) {
    Serial.println("No obstacle");
  } else {
    Serial.println("Obstacle detected");
  }
  Serial.println("------------------------------------");
  delay(500);  // Pause between the measurement of 500ms
}
