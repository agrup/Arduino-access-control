//#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SD.h>
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
  ethernet_init();
  leds_init();
  time_init();
  display_init();
  finger_init();
  card_init();
}

void loop() 
{
  print_time();  
  ethernet_listen();
  write_display("Esperando...    ",0,0);  
  read_card();
  read_finger();  
}
