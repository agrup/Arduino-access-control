//#include <ArduinoJson.h>
//#include <Ethernet.h>
//#include <SD.h>
#include "sd/sd_fp.h"
#include "ethernet/ethernet.h"

#include "fingerprint/FingerPrint.h"
#include "display/Display.h"
#include "rf-id/Rfid.h"
#include "time/time.h"
#include "leds/led.h"


void setup() 
{
  Serial.begin(9600);
  delay(100);
  ethernet_init();
  delay(100);
  card_init();
  delay(100);
  leds_init();
  delay(100);
  time_init();
  delay(100);
  display_init();
  delay(100);
  finger_init();
  
}

void loop() 
{
  print_time();  
  ethernet_listen();
  write_display("Esperando...    ",0,0);  
  read_card();
  read_finger();  
}
