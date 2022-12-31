// esp32 maitre bras robotique
// je charge la bibliothèque qui nous permet de communiquer
// avec les composants utilisant le protocole I2C
#include <Wire.h>


// Définition des adresses logiques des esclaves I2C.
#define I2C_SLAVE_ADDRESS  11

char* values ;
int nbTour = 1;
int debut = 0;
int fin = 0;

// ---------------------------------------------------------------------------
// Un programme Arduino doit impérativement contenir la fonction "setup"
// Elle ne sera exécuter une seule fois au démarrage du microcontroleur
// Elle sert à configurer globalement les entrées sorties
// ---------------------------------------------------------------------------
void setup()
{
  // Ouvre le port série et fixe le debit de communication à 9600 bauds
  Serial.begin(9600);

  // Initialise la library Wire et se connecte au bus I2C en tant que maître
  Wire.begin();

}

void SendValue(char* values, int slaveAddress) {

  // Envoie de la valeur à l'esclave I2C.
  // Principe et description :
  // 1 : Commencez une transmission vers la carte esclave I2C avec l'adresse donnee.
  // 2 : Ensuite, mettez en file d'attente les octets à transmettre avec la fonction write ()
  // 3 : transmettez-les en appelant la fonction endTransmission () .

  // débute de la communication avec un esclave (ouvre le stockage données à envoyer avec write)
  Wire.beginTransmission(slaveAddress);

  // charge des octets pour une transmission du composant maître vers un composant esclave
  //Wire.write(values);
  Wire.print(values);

  // Termine la transmission avec un composant esclave sur le bus I2C qui a été débutée avec
  // la fonction beginTransmission()
  Wire.endTransmission();

  // Affiche un message d'information pour l'operateur ensemble facultatif
  Serial.print("value : ");
  Serial.print(values);
  Serial.print("  to I2C Slave with logical address : ");
  Serial.println(slaveAddress);
}

// ---------------------------------------------------------------------------
// Le programme principal s’exécute par une boucle infinie appelée Loop ()
// ---------------------------------------------------------------------------

void loop() {
  delay(1000);

  if (nbTour == 1 ) {

    // repos WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // repos SHOULDER
    values = "s2180";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // repos ELBOW
    values = "s3100";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // repos WRIST_ROLL
    values = "s4100";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // repos WRIST_PITCH
    values = "s570";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // repos GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);

    delay(3000);

    // sequence
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // SHOULDER
    values = "s2140";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // ELBOW
    values = "s3150";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // WRIST_ROLL
    values = "s4100";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // WRIST_PITCH
    values = "s580";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // GRIPPER
    values = "s670";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // ELBOW
    values = "s380";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // WAIST
    values = "s1120";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // WAIST
    values = "s10";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // WAIST
    values = "s1180";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);

    nbTour = 0;
  }

  /*
    values = "ss60";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    values = "SAVE";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    values = "RESET";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
    values = "RUN";
    SendValue(values, I2C_SLAVE_ADDRESS);
    delay(1000);
  */
}
