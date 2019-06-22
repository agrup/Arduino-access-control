#include "fingerprint/FingerPrint.h"
#include "display/Display.h"
#include "rf-id/Rfid.h"
#include "time/time.h"
#include "leds/led.h"

boolean b = false;

void setup()  
{
  
  Serial.begin(9600);
  leds_init();
  time_init();
  display_init();
  finger_init();
  card_init();
}
void loop()                     // run over and over again
{
  if(b)
  {
    enrrol(4);
  }else
  {
    write_display("Esperando...    ",0,0);
    print_time();  
    read_card();
    read_finger();
  }
  
  
}
