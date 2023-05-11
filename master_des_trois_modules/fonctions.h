//==============================================================
// fonction d'envoi d'une valeur vers un des trois modules  I2C
//==============================================================
void SendValue(char* values, int slaveAddress) {

  // Envoie de la valeur a l'esclave I2C.
  // Principe et description :
  // 1 : Commencez une transmission vers la carte esclave I2C avec son adresse.
  // 2 : Ensuite, mettez en file d'attente les octets a transmettre avec la fonction write()
  // 3 : transmettez-les en appelant la fonction endTransmission() .

  // debute la communication avec un esclave (ouvre le stockage donnees a envoyer avec write)
  Wire.beginTransmission(slaveAddress);

  // charge des octets pour une transmission du composant master vers un composant esclave
  //Wire.write(values);
  Wire.print(values);

  // Termine la transmission avec un composant esclave sur le bus I2C qui a ete debutee avec
  // la fonction beginTransmission()
  Wire.endTransmission();

  // Affiche un message d'information pour l'operateur ( facultatif )
  Serial.print("value : ");
  Serial.print(values);
  Serial.print("  to I2C Slave with logical address : ");
  Serial.println(slaveAddress);
}

void reposBras() {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  delay(500);
  // repos WAIST
  values = "s190";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // repos SHOULDER
  values = "s2180";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // repos ELBOW
  values = "s3100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // repos WRIST_ROLL
  values = "s4100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // repos WRIST_PITCH
  values = "s570";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // repos GRIPPER
  values = "s6100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
}

void positionAttente() {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  // GRIPPER
  values = "s6120";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);

  // SHOULDER
  values = "s2160";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // ELBOW
  values = "s3120";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // WAIST
  values = "s110";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // WRIST_ROLL
  values = "s4100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  // WRIST_PITCH
  values = "s5100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
}

void attraper() {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  values = "s5100";  // relever la pince
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
  delay(500);
  values = "s3125"; // abaisser le bras s3 = on va mettre la variable values a s3=105
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
  delay(500);
  values = "s2109"; // abaisser le bras s3 = on va mettre la variable values a s3=105
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
  delay(500);
  values = "s662";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
  delay(500);
  values = "s3100";  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(500);
  /*
    values = "s5100";  // relever la pince
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);    // commande envoiyee i2c
    delay(500);
    values = "s3140"; // abaisser le bras s3 = on va mettre la variable values a s3=105
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
    delay(500);
    values = "s2130"; // abaisser le bras s3 = on va mettre la variable values a s3=105
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
    delay(500);
    // fermer la pince : s6 fermeture 60
    values = "s662";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
    delay(500);
    values = "s3130";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(500);
    values = "s380";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(500);
  */
}

void relacher()  {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  // ouvrir la pince : s6 ouverture 100
  values = "s6100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS); // envoie de la variable
  delay(1000);
}

void couleur_rouge() {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  values = "s1105";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
}

void couleur_vert() {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  values = "s1135";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
}

void couleur_bleu() {
#define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  values = "s1165";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(1000);
}
