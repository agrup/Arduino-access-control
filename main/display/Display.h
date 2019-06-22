#ifndef Display_h 
#define Display_h 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
//LiquidCrystal_I2C lcd(0x3F,16,2);  // Arduino Uno
LiquidCrystal_I2C lcd(0x27,16,2);  // Arduino Mega

void display_init()
{
    // Inicializar el LCD    
    lcd.init();  
    //Encender la luz de fondo.
    lcd.backlight();
}

void write_display(String text, int pos_x, int pos_y)
{
    // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)   
    lcd.setCursor(pos_x, pos_y);
    // Escribimos el Mensaje en el LCD.
    lcd.print(text);
}

#endif