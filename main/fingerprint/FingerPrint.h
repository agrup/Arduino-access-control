#ifndef FingerPrint_h 
#define FingerPrint_h 
#include "Arduino.h"
#include "../display/Display.h"
#include "../leds/led.h"
#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(A8, A9);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void finger_init()
{
  // set the data rate for the sensor serial port
  finger.begin(57600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  if (!finger.verifyPassword()) {
    Serial.println("Did not find fingerprint sensor :(");
  }
}

void error_huella()
{
  write_display("Error         ", 0, 0);
  red_led();
  delay(1000);
  off_leds();
}

uint8_t getFingerprintEnroll(int legajo) {
  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      error_huella();
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      error_huella();
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      error_huella();
      break;
    }
  }

  // OK success!
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      error_huella();
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      error_huella();
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      error_huella();
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      error_huella();
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      error_huella();
      Serial.println("Unknown error");
      return p;
  }
  write_display("Retire Huella                 ", 0, 0);
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  p = -1;
  write_display("Misma huella     ", 0, 0);
  delay(1000);
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      error_huella();
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      error_huella();
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      error_huella();
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      error_huella();
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      error_huella();
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      error_huella();
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      error_huella();
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    error_huella();
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    error_huella();
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    error_huella();
    Serial.println("Unknown error");
    return p;
  }   
  int id = get_next_id();
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {    
    String l = String(legajo);
    write_display("Huella Guardada   ", 0, 0);
    delay(1000);
    write_display("Legajo:"+String(legajo)+"                ", 0, 0);    
    save_person(String(id), l);
    delay(1000);
    Serial.println("Stored!");
    return true;
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    error_huella();
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    error_huella();
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    error_huella();
    Serial.println("Error writing to flash");
    return p;
  } else {
    error_huella();
    Serial.println("Unknown error");
    return p;
  }   
}

void enrol(int id)
{    
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  write_display("Ingrese Huella  ", 0, 0);
  if (id == 0) {// ID #0 not allowed, try again!
    error_huella();
    return;
  }
  Serial.print("Enrolling ID #");
  Serial.println(id);  
  while (!  getFingerprintEnroll(id) );
}
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int read_finger() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_NOTFOUND) 
  {
    write_display("No registrado       ", 0, 0);
    red_led();
    Serial.println("Did not find a match");
    delay(1000);
    off_leds();
  }
  if (p == FINGERPRINT_OK)
  {
    char s[16];
    String content = String(finger.fingerID);
    int exists = isperson(content);
    if(exists != -1)
    {
      save_fichada(String(exists), 0);
      sprintf(s, "Legajo:%i           ", exists);
      write_display(s, 0, 0);
      green_led();
      Serial.print("Found ID #"); Serial.print(finger.fingerID); 
      Serial.print(" with confidence of "); Serial.println(finger.confidence);
      delay(1000);
      off_leds();
    }else
    {
      write_display("No registrado            ", 0, 0);
      red_led();
      Serial.print("Found ID #"); Serial.print(finger.fingerID); 
      Serial.print(" with confidence of "); Serial.println(finger.confidence);
      delay(1000);
      off_leds();
    }
  }
}



#endif