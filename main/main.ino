<<<<<<< HEAD
//#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SD.h>
#include "sd/sd_fp.h"

int led = 6;

int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 2, 178 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 2, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;
String result_p;
void setup() {
   pinMode(4,OUTPUT); // set SD SPI slave select pin to OUTPUT
   digitalWrite(4,HIGH); // disable SD SPI interface. HIGH is disabled.
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
          if (readString.indexOf("?readfichada") < 0){
            
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='https://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Reloj Fichadas</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Reloj de fichadas</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Opciones</H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">Descargar Fichadas</a>");
           client.println("<a href=\"/?button1off\"\">Ver Ultima fichada</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<a href=\"/?savefichada\"\">Guardar fichada</a>");
           client.println("<a href=\"/?readfichada\"\">Leer fichada</a>");

          
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           //client.stop();
           //controls the Arduino if you press the buttons
          }else{
               if (readString.indexOf("?readfichada") >0){
               //String fichadas;
               StaticJsonDocument<200> doc;
               doc = readfile();
                client.flush();/*
               //client.println("</BODY>");
              //client.println("<meta http-equiv=refresh content=1;URL='//192.168.2.178/'>");
              //client.println("</HTML>");
                //client.println(fichadas);
                //while (myFile.available()) {
                  //String list = result_p.readStringUntil('\r');
                  //client.print("{\"users\": {\"nombre\": \"+list+}}");
                  Serial.println(fichadas);   */   
              client.println(F("HTTP/1.0 200 OK"));
              client.println(F("Content-Type: application/json"));
              client.println(F("Connection: close"));
              client.print(F("Content-Length: "));
              client.println(measureJsonPretty(doc));
              client.println();

  // Write JSON document
  serializeJsonPretty(doc, client);        
           }    
          }
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led, HIGH);
                            
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led, LOW);
              
           }
           if (readString.indexOf("?readfichada") >0){
           //    String fichadas;
             //  fichadas = readfile();
                
               //client.println("</BODY>");
              //client.println("<meta http-equiv=refresh content=1;URL='//192.168.2.178/'>");
              //client.println("</HTML>");

//                client.println(fichadas);
                //while (myFile.available()) {
                  //String list = result_p.readStringUntil('\r');
                  //client.print("{\"users\": {\"nombre\": \"+list+}}");
//                  Serial.println(fichadas);              
           }           
           if (readString.indexOf("?savefichada") >0){
             

            result_p = savefile("Agustin 10:30");
            client.flush();
 /*           
            client.print("{\"status\": {\"led_is\": \"on\"}}");
            client.print("{\"nombre\":"+);
            //client.println("<H3>");
            client.println(result_p);
            
            //client.println("HOLA");
            //client.println("</H3>");
*/
            
            Serial.println("initialization done.");
          
                          
           }
           if (readString.indexOf("?button2off") >0){

           }
            //clearing string for next read
            readString="";  
           client.stop();
         }
       }
    }
}
//fichada y enrolamiento
/*
#include "fingerprint/FingerPrint.h"
#include "display/Display.h"
#include "rf-id/Rfid.h"
#include "time/time.h"
#include "leds/led.h"

boolean b = false;

void setup()  
{
  
  Serial.begin(9600);
  leds_init();
  time_init();
  display_init();
  finger_init();
  card_init();
}
void loop()                     // run over and over again
{
  if(b)
  {
    enrrol(4);
  }else
  {
    write_display("Esperando...    ",0,0);
    print_time();  
    read_card();
    read_finger();
  }
  
  
}
*/