#ifndef led_h 
#define led_h 
#include "Arduino.h"

const int red = 6;
const int green = 7;

void leds_init()
{
    // Init leds
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
}

void green_led()
{
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(green, HIGH);   
  delay(1000);
  digitalWrite(green, LOW);
}

void red_led()
{
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(red, LOW);
}

void off_leds()
{
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
}

#endif