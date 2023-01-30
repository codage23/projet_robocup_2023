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
  delay(300);
  // repos WAIST
  values = "s190";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(300);
  // repos SHOULDER
  values = "s2180";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(300);
  // repos ELBOW
  values = "s3100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(300);
  // repos WRIST_ROLL
  values = "s4100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(300);
  // repos WRIST_PITCH
  values = "s570";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(300);
  // repos GRIPPER
  values = "s6100";
  SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
  delay(300);
}

void positionAttente() {
  #define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
    // GRIPPER
   values = "s6120";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(300);  
   // WAIST  
   values = "s190";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(300); 
   // SHOULDER
   values = "s2140";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(300); 
   // ELBOW
   values = "s380";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(300);
   // WRIST_ROLL
   values = "s4100";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(300); 
   // WRIST_PITCH
   values = "s560";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(300);
}

void sequenceRouge() {
  #define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  // sequence rouge
    // ELBOW
    values = "s3105";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s660";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // ELBOW
    values = "s380";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s1180";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
}

void sequenceVerte() {
  #define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  // sequence rouge
    // ELBOW
    values = "s3105";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s660";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // ELBOW
    values = "s380";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s1150";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
}

void sequenceBleue() {
  #define I2C_SLAVE_ADDRESS_BRAS  11
  char* values ;
  // sequence rouge
    // ELBOW
    values = "s3105";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s660";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // ELBOW
    values = "s380";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s1120";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // GRIPPER
    values = "s6100";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
    // WAIST
    values = "s190";
    SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
    delay(1000);
}
