#ifndef time_h 
#define time_h 
//#include <DateTime.h>
#include "../display/Display.h"
#include <Wire.h>
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

void print_time () {
    DateTime hoy = rtc.now();
    char s[8];
    sprintf(s, "Hora:%.2i:%.2i", hoy.hour(), hoy.minute(), hoy.second());
    write_display(s, 0, 1);
}
#endif