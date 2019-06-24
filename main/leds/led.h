#ifndef led_h 
#define led_h 
#include "Arduino.h"

const int red = 6;
const int green = 7;
const int buzzer = 11;
void leds_init()
{
    // Init leds
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(buzzer, OUTPUT);
}

void ring()
{
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1s
}

void green_led()
{
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(green, HIGH);   
  ring();
  //delay(1000);
  //digitalWrite(green, LOW);
}
void green_led_off()
{
 //digitalWrite(red, LOW);
  digitalWrite(green, LOW);

}

void red_led()
{
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    digitalWrite(red, HIGH);
    //delay(1000);
    digitalWrite(red, LOW);
}

void off_leds()
{
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
}

#endif