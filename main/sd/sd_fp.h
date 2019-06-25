#ifndef sd_fp_h
#define sd_fp_h
#include <SPI.h>
#include <SD.h> 
#include "Arduino.h"
#include <ArduinoJson.h>
//#include "../time/time.h"
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


StaticJsonDocument<400> readfile()
{
  StaticJsonDocument<400> doc;
 // StaticJsonDocument<200> info;
  //String result_2[];           
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  Serial.println("initialization done. PERS.TXT");
  // re-open the file for reading:
  myFile = SD.open("PERS.TXT");
  
 //JsonArray data = doc.createNestedArray("fichadas");
  JsonObject root = doc.to<JsonObject>();
  if (myFile) {
    int i = 0;
    while (myFile.available()) {
      i++;
      String list = myFile.readStringUntil('\n');
      
      String hora = getValue(list,';',1);
      String nombre = getValue(list,';',0);

      
      if(list != NULL){
        JsonObject fichada = root.createNestedObject(String(i));
        fichada["nombre"]=nombre;
        fichada["fecha"] = "10-4-2019";
        fichada["hora"] = hora;
        serializeJsonPretty(doc, Serial);
      }

    }

  } else {

    Serial.println("error opening test.txt");
  }

 return doc;

}
int get_next_id(){
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  int id;
  int id_res;

  myFile = SD.open("ID.TXT");
  if (myFile) {    
    id = myFile.read();
    id_res = id;
    id = id + 1;
  } 
  myFile.close();
  myFile = SD.open("PERS.TXT",FILE_WRITE);
  myFile.println(id);
  myFile.close();
  return id_res;
}

bool isperson(String person){
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
    myFile = SD.open("PERS.TXT");
    if (myFile) {
      while (myFile.available()) {
        String list = myFile.readStringUntil('\n');
        String person_in_file = getValue(list, ";", 0);
        if(person_in_file.compareTo(person))
        {
          myFile.close();
          return true;
        }      
      }
    myFile.close();
    return false;
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
    //String t = get_time();
    //String d = get_date() ;
    String t="10.30";
    String d="12/12/2019";
    String s = content+";"+t+";"+d+";"+String(tipo);
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

#endif