#ifndef time_h 
#define time_h 
//#include <DateTime.h>
#include "../display/Display.h"
#include <Wire.h>
#include "Arduino.h"
#include <RTClib.h>

RTC_Millis rtc;     //Reloj por software
//RTC_DS1307 rtc;   //Reloj con DS1307
//RTC_DS3231 rtc;   //Reloj con DS3231

char diaSemana[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

void time_init () {
   //Para setear RTC con fecha y hora cuando se compila
   rtc.adjust(DateTime(2019, 11, 21, 11, 9, 0));
   //Para setear RTC a 21-MAR-2019 8:00:00
   //rtc.adjust(DateTime(2019, 3, 21, 8, 0, 0));
}

void print_time () 
{
    DateTime hoy = rtc.now();
    char s[8];
    sprintf(s, "Hora:%.2i:%.2i", hoy.hour(), hoy.minute());
    write_display(s, 0, 1);
}

String get_time()
{
    DateTime hoy = rtc.now();
    char s[5];
    sprintf(s, "%.2i:%.2i", hoy.hour(), hoy.minute());
    String res = String(s);
    return res;
}

String get_date()
{
    DateTime hoy = rtc.now();
    char s[10];
    sprintf(s, "%.2i/%.2i/%.4i", hoy.day(), hoy.month(), hoy.year());
    String res = String(s);
    return res;
}

#endif