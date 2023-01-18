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
