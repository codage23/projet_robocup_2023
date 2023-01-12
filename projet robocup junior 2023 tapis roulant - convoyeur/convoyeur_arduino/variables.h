//========================================================
// Controls supression of the MonPrintf function to serial
//========================================================
#define SERIAL_BAUD 9600   // vitesse moniteur serie
#define SerialMonitor   1
#define debug 1  // true for use Display log message if True

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST  0        // if 1 true,  0 false
#define I2C  1         // if 1 true,  0 false


//==========================================
// Affectation des broches de l'arduino uno
//==========================================
// Câblage:
// Broche 11 à IN1 sur le pilote ULN2003
// Broche 10 à IN2 sur le pilote ULN2003
// Broche 9 à IN3 sur le pilote ULN2003
// Broche 8 à IN4 sur le pilote ULN2003

//==================================================
// Definition de l'adresse logique de l'esclave I2C
//==================================================
#define I2C_SLAVE_CONVOYEUR  12

//==========
// Sensor IR
//==========
int IRSensor = 12; // connect IR sensor module to Arduino pin D12

int LED = 13;      // connect LED to Arduino pin 13

//==========
// Variables
//==========
//==================
// stepper
//==================
//the number of steps in one revolution of your motor (28BYJ-48) 2048 pas par tour
#define STEPS  2048

int motorSpeed = 8 ; // 6 a 16 grand max
int motorStep = 48;  
bool motorInverse = 0; // sens
bool stopStart = 1; // 0 stop et 1 start

//=====
// I2C
//=====
String dataIn = "";
int dataI2C = 0;
bool requestI2C = 0;

const unsigned int MAX_MESSAGE_LENGTH = 32;
static char message[MAX_MESSAGE_LENGTH]; // longueur maxi du message I2C
