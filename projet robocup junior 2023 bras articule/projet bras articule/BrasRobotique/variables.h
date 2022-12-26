//========================================================
// Controls supression of the MonPrintf function to serial
//========================================================
#define SERIAL_BAUD 9600   // vitesse moniteur serie
#define SerialMonitor   1
#define debug 1  // true for use Display log message if True

#define TEST  0  // if 1 true,  0 false
#define I2C  1   // if 1 true,  0 false

//==================================================================
// Bluetooth
// 38400 Default baud rate of the Bluetooth module hc05 et 9600 hc06
//===================================================================
// si presence du bluetooth
#define BLUETOOTH  0   // if 1 true,  0 false

#define SERIAL_BAUD_BLUETOOTH 9600   // vitesse du bluetooth

//==========================================
// Affectation des broches de l'arduino uno
//==========================================
#define WAIST 5
#define SHOULDER 6
#define ELBOW 7
#define WRIST_ROLL 8
#define WRIST_PITCH 9
#define GRIPPER 10

//==========
// Variables
//==========
//==================
// current position
//==================
int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos;

//==================
// previous position
//==================
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos;

//=============================
// for storing positions/steps
//=============================
int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50], servo05SP[50], servo06SP[50];

int speedDelay = 20;
int index = 0;
String dataIn = "";

//===========================
// Robot arm initial position
//===========================
#define PP_WAIST 90
#define PP_SHOULDER 170
#define PP_ELBOW 60
#define PP_WRIST_ROLL 100
#define PP_WRIST_PITCH 120
#define PP_GRIPPER 100
