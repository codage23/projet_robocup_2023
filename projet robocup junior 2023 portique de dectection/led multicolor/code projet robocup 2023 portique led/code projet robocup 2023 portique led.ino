/*
 * projet robocup 2023
 * portique de detection
 */

/* Couleurs (format RGB) */
const byte COLOR_BLACK = 0b000;
const byte COLOR_RED = 0b100;
const byte COLOR_GREEN = 0b010;
const byte COLOR_BLUE = 0b001;
const byte COLOR_MAGENTA = 0b101;
const byte COLOR_CYAN = 0b011;
const byte COLOR_YELLOW = 0b110;
const byte COLOR_WHITE = 0b111;

/* Broches */
const byte PIN_LED_R = 9;
const byte PIN_LED_G = 11;
const byte PIN_LED_B = 10;
const byte PIN_LED_RR = 7;
const byte PIN_LED_GG = 12;
const byte PIN_LED_BB = 8;

// Fonction setup(), appelée au démarrage de la carte Arduino
void setup() {

  // Initialise les broches
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_RR, OUTPUT);
  pinMode(PIN_LED_GG, OUTPUT);
  pinMode(PIN_LED_BB, OUTPUT);
  displayColor(COLOR_BLACK);
}

// Fonction loop(), appelée continuellement en boucle tant que la carte Arduino est alimentée
void loop() {

  /* Code de démonstration */
  displayColor(COLOR_RED);
  delay(1000);

  displayColor(COLOR_GREEN);
  delay(1000);

  displayColor(COLOR_BLUE);
  delay(1000);

  displayColor(COLOR_MAGENTA);
  delay(1000);

  displayColor(COLOR_CYAN);
  delay(1000);

  displayColor(COLOR_YELLOW);
  delay(1000);

  displayColor(COLOR_WHITE);
  delay(1000);

  displayColor(COLOR_BLACK);
  delay(1000);
}

void displayColor(byte color) {

  // Assigne l'état des broches
  // Version cathode commune
  digitalWrite(PIN_LED_R, bitRead(color, 2));
  digitalWrite(PIN_LED_G, bitRead(color, 1));
  digitalWrite(PIN_LED_B, bitRead(color, 0));
  digitalWrite(PIN_LED_RR, bitRead(color, 2));
  digitalWrite(PIN_LED_GG, bitRead(color, 1));
  digitalWrite(PIN_LED_BB, bitRead(color, 0));


  // Version anode commune
  //digitalWrite(PIN_LED_R, !bitRead(color, 2));
  //digitalWrite(PIN_LED_G, !bitRead(color, 1));
  //digitalWrite(PIN_LED_B, !bitRead(color, 0));
}