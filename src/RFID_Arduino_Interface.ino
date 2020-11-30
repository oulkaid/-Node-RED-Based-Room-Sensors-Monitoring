#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Création d'une instance de MFRC522

#define buzzer 7 // Le buzzer alarm qui accompagne l'opération de l'identification avce un Tag RFID

#define D0 2    // Le bit LSB de la donnée qui code la nom de la personne (voir tabeau ci-dessous) : valeur à envoyer vers l'autre Arduino
#define D1 4    // Le bit MSB de la donnée qui code la nom de la personne
#define ACK 5   // Le bit qui fait l'acquitement (ie. confirmation de la réception) : c'est un bit à lire, qui en prevenance de l'autre Arduino

/* D1 D0 ->(valeur)
 * 0  0  -> NULL
 * 0  1  -> oussama 
 * 1  0  -> ahal
 * 1  1  -> Inconnu
 */

void send_oussama(){     // Cette fonction est appelée lorsqu'on veut informer l'autre Arduino que Oussama a effectuer un accès
  digitalWrite(D0, HIGH);
  digitalWrite(D1, LOW);
  delay(100);
  while(!digitalRead(ACK)){}
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
}

void send_mohamed(){   // De même pour Mohamed
  digitalWrite(D0, LOW);
  digitalWrite(D1, HIGH);
  delay(100);
  while(!digitalRead(ACK)){}
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
}

void send_inconnu(){  // De même si l'on recennait pas le Tag RFID (personne inconnue)
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  delay(100);
  while(!digitalRead(ACK)){}
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
}
 
void setup()
{
  Serial.begin(9600);  // initialisation du port série
  SPI.begin();         // initialisation de la communication SPI propre au module RFID
  mfrc522.PCD_Init();  // initialisation de la fonction PDC_Init() de la bibliothèque MFRC22. ça permet de réinitialiser le module RFID pour qu'il soit prêt pour réaliser des lectures des Tags
  pinMode(buzzer, OUTPUT); // le buzzer alarm est dérigé vers une sortie numérique de l'Arduino
  digitalWrite(buzzer, LOW); // le buzzer alarm est initialement éteint
  
  pinMode(D0, OUTPUT); // Sortie numérique
  pinMode(D1, OUTPUT); // Sortie numérique
  pinMode(ACK, INPUT);  // Entrée analogique

  //-> l'envoi de "00" => initialement, personne n'est considéré présent
  digitalWrite(D0, LOW);  
  digitalWrite(D1, LOW);
}

void loop()
{
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  
  // Recherche d'une nouvelle carte/Tag RFID
if (mfrc522.PICC_IsNewCardPresent()) 
{
  // Sélection d'une carte/Tag RFID
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  digitalWrite(buzzer, HIGH); // lancement du buzzer
  String content= ""; // cette valeur contient à chaque fois la personne qui est présente
  //-> la partie suivante permet de préparer l'identifiant de la carte/Tag RFID et de l'affecter à la variable : content.substring(1). Cette variable sera tester à chaque fois
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  // tester content.substring(1) pour savooir de quoi il s'agit parmi les personnes connues
  if(content.substring(1) == "C5 E8 D3 65") {send_oussama();}
  else if(content.substring(1) == "55 31 D4 65") {send_mohamed();}
  else {send_inconnu();}
  delay(200);
}
  
  digitalWrite(buzzer, LOW); // éteindre le buzzer alarm
  delay(100);
  
}
