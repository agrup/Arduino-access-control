//#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SD.h>
#include "sd/sd_fp.h"
#include "ethernet/ethernet.h"
/*
int led = 6;

int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 2, 178 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 2, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;
String result_p;
*/
void setup() {
  Serial.begin(9600);
  ethernet_init();
}


void loop() {
  ethernet_listen();
}
//fichada y enrolamiento
