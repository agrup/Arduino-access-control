#ifndef sd_fp_h
#define sd_fp_h
#include <SPI.h>
#include <SD.h> 
#include "Arduino.h"
#include <ArduinoJson.h>
#include "../time/time.h"

File myFile;
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


StaticJsonDocument<200> readfile()
{
  StaticJsonDocument<200> doc;
  //String result_2[];           
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  Serial.println("initialization done.");
  // re-open the file for reading:
  myFile = SD.open("PERS.TXT");
  if (myFile) {
    while (myFile.available()) {
      String list = myFile.readStringUntil('\n');
      Serial.println(list);
      String aux = getValue(list," ",0);

      Serial.println(aux);
      doc["nombre"] = list;
      doc["time"] = 1351824120;
    }

  } else {

    Serial.println("error opening test.txt");
  }

 return doc;

}
int get_next_id(){
<<<<<<< HEAD
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    //while (1);
  }
  myFile = SD.open("ID.TXT");
  if (myFile) {    
    long id = myFile.read();
    int id_res = id;
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
    String s = content+";"+t+";"+d+";"+String(tipo);
    myFile.println(s);
    myFile.close();

  } else {
    Serial.println("error opening test.txt");
  }
 
=======
  return 3;
}

bool isperson(String person){
  return true;
>>>>>>> 0faa644e82ce5767822c9bd2a96486ece3bc563e
}

void save_person(int id,int legajo){
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
    //while (1);
    }
    myFile = SD.open("PERS.TXT",FILE_WRITE);
    if (myFile) {
      Serial.println("open file");
      String s = String(id)+";"+String(legajo);
      myFile.println(s);
      myFile.close();

    } else {
      Serial.println("error opening test.txt");
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