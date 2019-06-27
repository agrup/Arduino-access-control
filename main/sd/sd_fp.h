#ifndef sd_fp_h
#define sd_fp_h
#include <SPI.h>
#include <SD.h> 
#include "Arduino.h"
#include <ArduinoJson.h>
#include "../time/time.h"
#include "../leds/led.h"

File myFile;

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 2;

    
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        //Serial.println(data.charAt(i));

        if  (data.charAt(i) == separator || i == maxIndex ) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


//JsonDocument<1200> readfile()
DynamicJsonDocument readfile()
{
  //StaticJsonDocument<1200> doc;
  DynamicJsonDocument doc(2048);
 // StaticJsonDocument<200> info;
  //String result_2[];           
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  Serial.println("initialization done. PERS.TXT");
  // re-open the file for reading:
  myFile = SD.open("FICH.TXT");
  
 //JsonArray data = doc.createNestedArray("fichadas");
  JsonObject root = doc.to<JsonObject>();
  if (myFile) {
    int i = 0;
    while (myFile.available()) {
      i++;
      String list = myFile.readStringUntil('\n');
      //String s = content+";"+t+";"+d+";"+String(tipo);
      String hora = getValue(list,';',1);
      String legajo = getValue(list,';',0);
      String fecha = getValue(list,';',2);
      String tipo = getValue(list,';',3);
      
      if(list != NULL){
        JsonObject fichada = root.createNestedObject(String(i));
        fichada["Legajo"]=legajo;
        fichada["fecha"] = fecha;
        fichada["hora"] = hora;
        fichada["tipo"] = tipo;
        serializeJsonPretty(doc, Serial);
      }      
    }
    myFile.close();

  } else {

    Serial.println("error opening test.txt");
  }

 return doc;

}

void reset_ids()
{
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  SD.remove("ID.TXT");
  File f = SD.open("ID.TXT",FILE_WRITE);
  f.write(1);  
  f.close();
}

int get_next_id(){
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }  
  int id;
  int id_res;
  int int_id;
  File file = SD.open("ID.TXT", FILE_READ);
  if (file) {        
    id = file.read();
    Serial.print("ID leido: ");
    Serial.println(id);
    
    id_res = id;
    int_id = id + 1;
    Serial.print("ID sumado: ");
    Serial.print(int_id);
    file.close();
  }   
  SD.remove("ID.TXT");
  file = SD.open("ID.TXT",FILE_WRITE);
  Serial.print("ID a grabar: ");
  Serial.println(int_id);  
  file.write(int_id);
  file.close();
  return id_res;
}

int isperson(String person){
  int res = -1;
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
    myFile = SD.open("PERS.TXT");
    if (myFile) {
      while (myFile.available()) {
        String list = myFile.readStringUntil('\n');
        String person_in_file = getValue(list, ';', 0);
        String legajo = getValue(list, ';', 1);
        Serial.println(person);
        Serial.println(person_in_file);
        if(person_in_file.compareTo(person)==0)
        {
          Serial.println("lalaal");
          myFile.close();
          Serial.println(legajo);
          return legajo.toInt();
        }      
      }
    myFile.close();
    return res;
  }
}

void save_fichada(String content, int tipo)
{
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  Serial.println("initialization done.");
  // re-open the file for reading:
  myFile = SD.open("FICH.TXT",FILE_WRITE);
  if (myFile) {
    String t = get_time();
    String d = get_date() ;
    //String t="10.30";
    //String d="12/12/2019";
    String s = content+";"+t+";"+d+";"+String(tipo);
    Serial.println(s);
    myFile.println(s);
    myFile.close();

  } else {
    Serial.println("error opening test.txt");
  }
 
}

void save_person(String id,String legajo){
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
    //while (1);
    }
    myFile = SD.open("PERS.TXT",FILE_WRITE);
    if (myFile) {
      Serial.println("open file");
      String s = id+";"+legajo;
      Serial.println(s);
      myFile.println(s);
      myFile.close();

    } else {
      Serial.println("error opening ");
    }
}



String savefile(String persona)
{
            
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  Serial.println("initialization done.");
  // re-open the file for reading:
  myFile = SD.open("PERS.TXT",FILE_WRITE);
  if (myFile) {
    Serial.println("open file");
    myFile.println(persona);
    myFile.close();

  } else {
    Serial.println("error opening test.txt");
  }
 return persona;

}

void clear_fichadas()
{
  SD.remove("FICH.TXT");
  File file = SD.open("FICH.TXT",FILE_WRITE);
  file.close();
  write_display("Reset Fichadas           ", 0, 0);
  green_led();  
  delay(1000);
  off_leds();
}

void clear_ids()
{
  SD.remove("ID.TXT");
  File file = SD.open("ID.TXT",FILE_WRITE);  
  file.write(1);
  file.close();
  write_display("Reset IDs           ", 0, 0);
  green_led();
  delay(1000);
  off_leds();  
}

void clear_persons()
{
  SD.remove("PERS.TXT");
  File file = SD.open("PERS.TXT",FILE_WRITE);
  file.close();
  write_display("Reset Personas           ", 0, 0);
  green_led();
  delay(1000);
  off_leds();
}

#endif