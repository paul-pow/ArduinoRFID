#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen

#define SS_PIN 53 
#define RST_PIN 5 

#define SS_PIN_2 48 
#define RST_PIN_2 6 

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benennen
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_2); // RFID-Empfänger benennen

void LesenAusgeben(){ //Diese Methode liest den Chip am ersten Sensor aus speichert seinen Code in ein Array und gibt ihn aus
  if ( ! mfrc522.PICC_IsNewCardPresent()) // Wenn keine Karte in Reichweite ist...
    {
    return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
    }

  if ( ! mfrc522.PICC_ReadCardSerial()) // Wenn kein RFID-Sender ausgewählt wurde
    {
    return; // ...springt das Programm zurück vor die if-Schleife, womit sich die Abfrage wiederholt.
    }

  Serial.print("Die ID des RFID-TAGS lautet:"); // "Die ID des RFID-TAGS lautet:" wird auf den Serial Monitor geschrieben.

  for (byte i = 0; i < mfrc522.uid.size; i++)
    {
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet. Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
    Serial.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
    }

  Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.
  }


void setup(){ // Beginn des Setups:
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)
  SPI.begin(); // SPI-Verbindung aufbauen

  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers zum Lesen und Ausgeben
  mfrc522_2.PCD_Init(); // Initialisierung des RFID-Empfängers zum schreiben der Whitelist
}



void loop() {// Hier beginnt der Loop-Teil
LesenAusgeben();
}
