//========================================================
// Controls supression of the MonPrintf function to serial
//========================================================
#define SERIAL_BAUD 9600   // vitesse moniteur serie
#define SerialMonitor   1
#define DEBUG 0  // true for use Display log message if True

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST  0        // if 1 true,  0 false
#define I2C  1         // if 1 true,  0 false

//==========================================
// Affectation des broches de l'arduino uno
//==========================================
// Cablage

int ledRed = 9;
int ledGreen = 11;
int ledBlue = 10;

int ledRed1 = 7;
int ledGreen1 = 12;
int ledBlue1 = 8;
int resultatLed1 = 0;

#define ledsBlanches A0

//===========================
// TCS3200 detecteur couleurs
//===========================
#define S0 6
#define S1 5
#define S2 4
#define S3 3
#define sensorOut 2

//==================================================
// Definition de l'adresse logique de l'esclave I2C
//==================================================
#define I2C_SLAVE_PORTIQUE  14

//==========
// Sensor IR
//==========
#define IRSensor  13 // connect IR sensor module to Arduino pin D13

//==========
// Variables
//==========
//=====================
// detecteur couleurs
//=====================
int frequencyRed = 0;
int frequencyGreen = 0;
int frequencyBlue = 0;

int red_value = 0;
int green_value = 0;
int blue_value = 0;
int couleur = 0;

bool colorFind = false;

int sensor_ir = 0;            // variable pour l'etat actuel du bouton poussoir
int sensor_ir_mem = 0;        // variable pour l'etat precedent du bouton poussoir

//=====
// I2C
//=====
String dataIn = "";
int dataI2C = 0;
bool requestI2C = 0;

const unsigned int MAX_MESSAGE_LENGTH = 32;
static char message[MAX_MESSAGE_LENGTH]; // longueur maxi du message I2C
