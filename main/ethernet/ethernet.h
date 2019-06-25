#ifndef ethernet_h
#define ethernet_h
#include <Ethernet.h>
#include <SD.h>
#include "../sd/sd_fp.h"
#include "../leds/led.h"
#include "../fingerprint/FingerPrint.h"
#include "../rf-id/Rfid.h"



int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 2, 178 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 2, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;
String result_p;

void ethernet_init(){
    pinMode(4,OUTPUT); // set SD SPI slave select pin to OUTPUT
    digitalWrite(4,HIGH); // disable SD SPI interface. HIGH is disabled.
    /*while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }*/
    //pinMode(led, OUTPUT);
    Ethernet.begin(mac, ip, gateway, subnet);
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
    // green_led(); 
    // delay(500);
    // green_led_off();
}


void ethernet_listen(){
  //ethernet_init();
     // Create a client connection
  bool flag = false;
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
          // mostrar fichadas     
          if (readString.indexOf("?readfichada") > 0){
              //StaticJsonDocument<800> doc;
              DynamicJsonDocument
              doc = readfile();
              client.flush();   
              client.println(F("HTTP/1.0 200 OK"));
              client.println(F("Content-Type: application/json"));
              client.println(F("Connection: close"));
              client.print(F("Content-Length: "));
              client.println(measureJsonPretty(doc));
              client.println();

                serializeJsonPretty(doc, client);
                flag = true;
          }
          if (readString.indexOf("?newlegajo") > 0){ 
            int pos1 = readString.indexOf('=');
            int pos2 = readString.indexOf('&');
            String newString = readString.substring(pos1+1, pos2);
            Serial.print("newString is: ");
            Serial.println(newString);
            int val = newString.toInt();
            enrol(val);
            Serial.println(val);
          }
          if (readString.indexOf("?newcard") > 0){ 
            int pos1 = readString.indexOf('=');
            int pos2 = readString.indexOf('&');
            String newString = readString.substring(pos1+1, pos2);
            Serial.print("newString is: ");
            Serial.println(newString);
            int val = newString.toInt();
            add_card(newString);
            Serial.println(val);
          }
          if (readString.indexOf("?enrolar") > 0){ 
              client.println("HTTP/1.1 200 OK"); //send new page
              client.println("Content-Type: text/html");
              client.println();     
              client.println("<HTML>");
              client.println("<HEAD>");
              client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
              client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
              client.println("<link rel='stylesheet' type='text/css' href='https://randomnerdtutorials.com/ethernetcss.css' />");
              client.println("<TITLE>Enrolar</TITLE>");
              client.println("</HEAD>");
              client.println("<BODY>");
              client.println("<H2>Enrolando</H2>");
              client.println("<br />");  
              client.println("<a href=\"/?enrolar\"\">enrolar</a>");  
              client.println("<br />");
              client.println("<FORM ACTION='/?newlegajo/' method=get >"); //uses IP/port of web page
              client.println("<br />");
              client.println("Legajo: <INPUT TYPE=TEXT NAME='newlegajo' VALUE='' SIZE='25' MAXLENGTH='50'><BR>");
              client.println("<INPUT TYPE=SUBMIT NAME='submit' VALUE='Enrolar'>");
              client.println("</FORM>");          
              client.println("</BODY>");
              client.println("</HTML>");
              flag = true;
          }
          if (readString.indexOf("?card") > 0){ 
              client.println("HTTP/1.1 200 OK"); //send new page
              client.println("Content-Type: text/html");
              client.println();     
              client.println("<HTML>");
              client.println("<HEAD>");
              client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
              client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
              client.println("<link rel='stylesheet' type='text/css' href='https://randomnerdtutorials.com/ethernetcss.css' />");
              client.println("<TITLE>Enrolar Tarjeta</TITLE>");
              client.println("</HEAD>");
              client.println("<BODY>");
              client.println("<H2>Enrolando</H2>");
              client.println("<br />");  
              //client.println("<a href=\"/?enrolar\"\">enrolar</a>");  
              client.println("<br />");
              client.println("<FORM ACTION='/?newcard/' method=get >"); //uses IP/port of web page
              client.println("<br />");
              client.println("Legajo: <INPUT TYPE=TEXT NAME='newcard' VALUE='' SIZE='25' MAXLENGTH='50'><BR>");
              client.println("<INPUT TYPE=SUBMIT NAME='submit' VALUE='Enrolar-Card'>");
              client.println("</FORM>");          
              client.println("</BODY>");
              client.println("</HTML>");
              flag = true;
          }          
            // enrolar personas
           
            if (!flag){   
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
              // client.println("<br />");  
              // client.println("<a href=\"/?button1on\"\">Descargar Fichadas</a>");
               client.println("<a href=\"/?card\"\">Enrolar con tarjeta</a><br />");   
              client.println("<br />");     
              client.println("<br />"); 
              client.println("<a href=\"/?savefichada\"\">Guardar fichada</a>");
              client.println("<a href=\"/?readfichada\"\">Leer fichada</a>");
              client.println("<a href=\"/?enrolar\"\">enrolar</a>"); 
              client.println("<br />"); 
              client.println("</BODY>");
              client.println("</HTML>");
              delay(1);

            if (readString.indexOf("?button1on") >0){
               // digitalWrite(led, HIGH);
                              
            }
            if (readString.indexOf("?button1off") >0){
                //digitalWrite(led, LOW);
                
            }
        
            if (readString.indexOf("?savefichada") >0){
              

              savefile("Agu;10:30");
              savefile("Mario;11:30");
              
              client.flush();

              
              Serial.println("initialization done.");
            
                            
            }
            if (readString.indexOf("?button2off") >0){

            }
            }
            readString="";  
           client.stop();

         }
       }
    }
}
}


#endif

