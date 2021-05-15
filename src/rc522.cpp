#include "rc522.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

void RC522Init(){
    SPI.begin();               // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522 card
}

unsigned int RC522Read(){
    unsigned int hex_num=0;
    while ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      delay(1000);
      return 0;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return 0;
    }
    Serial.print("Card UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {

    hex_num =  mfrc522.uid.uidByte[0] << 24;
    hex_num += mfrc522.uid.uidByte[1] << 16;
    hex_num += mfrc522.uid.uidByte[2] <<  8;
    hex_num += mfrc522.uid.uidByte[3];

    } 
   //Serial.println(hex_num);
   return hex_num;
}