#ifndef Rfid_h 
#define Rfid_h 
#include <SPI.h>
#include <MFRC522.h>
#include "../display/Display.h"
#include "../leds/led.h"

// For Arduino UNO
//#define SS_PIN 10
//#define RST_PIN 9
// For Arduino MEGA
#define SS_PIN 53
#define RST_PIN 49

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[3];

void card_init()
{
    SPI.begin(); // Init SPI comunication
    rfid.PCD_Init();      // Init library MFRC522 
    Serial.println("Sistema rfid iniciado, esperando tarjeta.");
}

void read_card()
{   
    // Search card
    if ( rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String content= "";
        byte letter;
        for (byte i = 0; i < rfid.uid.size; i++)  {
            content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : ""));
            content.concat(String(rfid.uid.uidByte[i], DEC));
        }        
        Serial.println("ID de tarjeta:"+ content);      
        int b = isperson(content);
        if (b!=-1)
        {
            save_fichada(String(b), 1);
            write_display("Legajo:"+String(b)+"        ", 0, 0);
            green_led();
            delay(1000);
            off_leds();
            Serial.println("Legajo:"+ String(b));      
        }else
        {
            write_display("No Registrado               ", 0, 0);
            red_led();
            delay(1000);
            off_leds();
            Serial.println("ID de tarjeta:"+ content);      
        }          
    }
}

void add_card(String legajo)
{    
     // Search card else call add_card
    if ( rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) 
    {
        String content= "";
        byte letter;
        for (byte i = 0; i < rfid.uid.size; i++)  {
            content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : ""));
            content.concat(String(rfid.uid.uidByte[i], DEC));
        }
        save_person(content,legajo);
        write_display("Tarjeta agregada         ", 0, 0);              
        delay(1000);
        write_display("Legajo:"+legajo+"            ", 0, 0);              
        delay(1000);
        write_display("Retire tarjeta            ", 0, 0);              
        delay(2000);
    }
    else
    {
        add_card(legajo);
    }
}

#endif