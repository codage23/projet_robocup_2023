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
// Variables
//==========
//==================
// stepper
//==================
//the number of steps in one revolution of your motor (28BYJ-48)
#define STEPS  2048

int motorSpeed = 8; // 10 a 15 grand max
int motorStep = 2048;  // 2048 pas par tour
int motorStepInverse = -2048; // autre sens
String dataIn = "";
int dataI2C = 0;

const unsigned int MAX_MESSAGE_LENGTH = 32;
static char message[MAX_MESSAGE_LENGTH]; // longueur maxi du message I2C
