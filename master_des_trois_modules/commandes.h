/*
  Projet robocup 2023 - tri d’objets de couleur

  //==============================================================
  Commandes pour le portique de détection : @ 14
  //==============================================================
  pc   pour renvoyer au master la couleur détectée (1 rouge, 2 verte, 3 bleue, 0 sans)
   ex: values = "pc";  // demande couleur
       SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE);    // envoi i2c
       Wire.requestFrom(I2C_SLAVE_ADDRESS_PORTIQUE, 1);  // lecture de la valeur en retour
       while (Wire.available())  {                       // attente des octets i2c
       char c = Wire.read();
       if ( c == 1 ) {        }

  pl(xx) pour allumer une led avec la couleur choisie (10 rouge, 20 verte, 30 bleue, 00 sans)
   ex:  values = "pl10";  // led rouge
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c

  RESET pour remettre à zéro le portique de détection
   ex:  values = "RESET";  // led rouge
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c

  //==============================================================
  Commandes pour le convoyeur : @12
  //==============================================================
  sc  pour renvoyer au master la situation du convoyeur (0  objet present , 1   objet absent)
   ex: values = "sc";  // demande etat objet
       SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);    // envoi i2c
       Wire.requestFrom(I2C_SLAVE_ADDRESS_CONVOYEUR, 1);  // lecture de la valeur en retour
       while (Wire.available())  {                        // attente des octets i2c
       char c = Wire.read();
       if ( c == 1 ) {        }
       else {   }

  mv(xx) pour choisir la vitesse du convoyeur ( de 6 a 16 maxi) (8 au démarrage)
   ex:  values = "mv6"; // envoi de 6
        SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);

  mp(xxx) pour le nombre de pas (de 0 à 2048 maxi) (48 au démarrage)
   ex:  values = "mp96"; // envoi de 96
        SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);

  ms(x) pour le sens de rotation (0 ou 1) (0 au démarrage)
   ex:  values = "ms11"; // envoi de 1
        SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);

  STOP ou START   (START au démarrage)
   ex:  values = "STOP";
        SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);

  //==============================================================
  Commandes pour le bras articule : @ 11
  //==============================================================
  s1(xxx) pour modifier la position du servo "Waist_taille" ( de 00 à 180 maxi) (90 au démarrage)
   ex:  values = "s190"; // envoi de 90
        SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

  s2(xxx) pour modifier la position du servo "shoulder_epaule" ( de 90 à 180 maxi) (180 au démarrage)
   ex: values = "s2140"; // envoi de 140
       SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

  s3(xxx) pour modifier la position du servo "elbow_coude" ( de 30 à 150 maxi) (100 au démarrage)
   ex: values = "s3150"; // envoi de 150
       SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

  s4(xxx) pour modifier la position du servo "wrist roll_rotation du poignet" ( de 80 à 170 maxi) (100 au démarrage)
   ex: values = "s4100"; // envoi de 100
       SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

  s5(xxx) pour modifier la position du servo "wrist pitch_hauteur du poignet" ( de 40 à 120 maxi) (70 au démarrage)
   ex: values = "s580";  // envoi de 80
       SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

  s6(xxx) pour modifier la position du servo "gripper_pince" ( de 48 à 150 maxi) (100 au démarrage)
   ex: values = "s670";  // envoi de 70
       SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

  RESET pour remettre le bras en position d’attente.
   ex: values = "RESET";
       SendValue(values, I2C_SLAVE_ADDRESS_BRAS);

*/

/*
  exemple de sequence pour le portique avec affichage de la couleur recue avec la commande pc
  
  if (nbTour == 1 ) {
    // demande a recevoir 1 octets du peripherique d'adresse 14
    values = "pc";  // demande couleur
    SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
    Wire.requestFrom(I2C_SLAVE_ADDRESS_PORTIQUE, 1);

    while (Wire.available())  {    // attente des octets i2c
      char c = Wire.read();
      if ( c == 1 ) {
        values = "pl10";  // led rouge
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      } else if ( c == 2 ) {
        values = "pl20";  // led verte
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); //envoi i2c
      } else if ( c == 3 ) {
        values = "pl30"; // led bleue
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE); // envoi i2c
      } else {
        values = "pl00";  // led eteinte
        SendValue(values, I2C_SLAVE_ADDRESS_PORTIQUE);
      }
      c = c + 48;  //  chiffre charactere ascii
      Serial.println(c);  // envoi à la console
    }
  }
*/

/*
  exemple de sequence pour le bras : reset suivi d'une sequence tout cela une seule fois

  if (nbTour == 1 ) {
   // repos WAIST
   values = "s190";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // repos SHOULDER
   values = "s2180";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // repos ELBOW
   values = "s3100";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // repos WRIST_ROLL
   values = "s4100";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // repos WRIST_PITCH
   values = "s570";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // repos GRIPPER
   values = "s6100";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);

   delay(3000);

   // sequence
   // WAIST
   values = "s190";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // SHOULDER
   values = "s2140";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // ELBOW
   values = "s3150";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // WRIST_ROLL
   values = "s4100";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // WRIST_PITCH
   values = "s580";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // GRIPPER
   values = "s670";
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
   values = "s10";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // WAIST
   values = "s1180";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);
   // WAIST
   values = "s190";
   SendValue(values, I2C_SLAVE_ADDRESS_BRAS);
   delay(1000);

   nbTour = 0;
  }
*/
/*
  exemple de sequence pour le convoyeur

  values = "ms0";
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
  values = "mv8";
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
  values = "mp48";
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);
  delay(500);
  values = "sc";  // demande etat objet
  SendValue(values, I2C_SLAVE_ADDRESS_CONVOYEUR);    // envoi i2c
  Wire.requestFrom(I2C_SLAVE_ADDRESS_CONVOYEUR, 1);  // lecture de la valeur en retour
  while (Wire.available())  {                        // attente des octets i2c
    char c = Wire.read();
    if ( c == 1 ) {
      Serial.println("reception objet absent");
    }
    else {
      Serial.println("reception objet present");
    }
  }

*/
