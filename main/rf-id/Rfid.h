#ifndef Rfid_h 
#define Rfid_h 
#include <SPI.h>
#include <MFRC522.h>
#include "../display/Display.h"
#include "../leds/led.h"

// Para Arduino UNO
//#define SS_PIN 10
//#define RST_PIN 9
// Para Arduino MEGA
#define SS_PIN 53
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[3];

void card_init()
{
    SPI.begin(); // Inicia la comunicación SPI
    rfid.PCD_Init();      // inicia la libreria MFRC522 
    Serial.println("Sistema rfid iniciado, esperando tarjeta.");
}

void read_card()
{   
    // Buscamos tarjetas y las lee
    if ( rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String content= "";
        byte letter;
        for (byte i = 0; i < rfid.uid.size; i++)  {
            content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
            content.concat(String(rfid.uid.uidByte[i], DEC));
        }        
        bool b =isperson(content);
        if (b)
        {
            save_fichada(content, 1);
            write_display("Id:"+content, 0, 0);
            green_led();
            delay(1000);
            Serial.println("ID de tarjeta:"+ content);      
        }else
        {
            write_display("No válido", 0, 0);
            green_led();
            delay(1000);
            Serial.println("ID de tarjeta:"+ content);      
        }  
        
    }    
}

void add_card(String legajo)
{
    
     // Buscamos tarjetas y las lee
    if ( rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) 
    {
        String content= "";
        byte letter;
        for (byte i = 0; i < rfid.uid.size; i++)  {
            content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : ""));
            content.concat(String(rfid.uid.uidByte[i], DEC));
        }
        write_display("ID:"+content, 0, 0);
        //int l = (int) legajo;
        save_person(content,legajo);
        // Asociamos el id de persona con la tarjeta
        //save_person_card(id, content);     
        write_display("Tarjeta agregada  ", 0, 0);              
        delay(1000);
    }
    
}

#endif