
#include <SPI.h>
#include <SD.h> 
#include "Arduino.h"
#include <ArduinoJson.h>

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
  String result="{";
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
      doc["nombre"] = list;
      doc["time"] = 1351824120;



  // Add values in the object
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root.set<long>("time", 1351824120);



  //serializeJson(doc, Serial);


  Serial.println();

      // Serial.write(myFile.read());
      // result += myFile.read();
    }

      // myFile.close();

  } else {

    Serial.println("error opening test.txt");
  }
  result += "}";
 return doc;

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

