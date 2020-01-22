/*
 * Sketch: ESP8266_LED_Control_02C
 * Now with added CSS and a single button
 * Control an LED from a web browser
 * Intended to be run on an ESP8266
 * 
 * connect to the ESP8266 AP then
 * use web broswer to go to 192.168.4.1
 * 
 */
#include <ESP8266WiFi.h>
const char WiFiPassword[] = "Eparao20!!";
const char AP_NameChar[] = "COMPefixe" ;
 
WiFiServer server(80);
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>TESTING</title></head><body><div id='main'><h2>TESTING</h2>";
String html_2 = "";
String html_3 = "";
String html_4 = "";
String html_5 = "";
String html_6 = "";
String html_7 = "";
String html_8 = "";
String html_9 = "";
String end = "</div></body></html>"; 
String request = "";


 
void setup() 
{
    Serial.begin(9600);
    WiFi.softAP(AP_NameChar, WiFiPassword);
    server.begin();
 
} // void setup()
 
char* ptr = NULL;
char *strings[10];

void loop() 
{
    String minute = "";
    String hour = "";
    String day = "";
    String month = "";
    String year = "";
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
    if       ( request.indexOf("u") > 0 ) {Serial.print("u");}
    else if  ( request.indexOf("t") > 0 ) {Serial.print("t");}
    else if  ( request.indexOf("d") > 0 ) {Serial.print("d");}
    else if  ( request.indexOf("w") > 0 ) {Serial.print("w");}
    else if  ( request.indexOf("b") > 0 ) {Serial.print("b");}
    else if  ( request.indexOf("p") > 0 ) {Serial.print("p");}
    else if  ( request.indexOf("r") > 0 ) {Serial.print("r");}
    else if  ( request.indexOf("k") > 0 ) {Serial.print("k");}
    else if  ( request.indexOf("h") > 0 ) {
      for(int i = (request.indexOf("h")+1); i < request.indexOf("+"); i++){
        day = day + request[i];
      }
      for(int i = (request.indexOf("+")+1); i < request.indexOf("&"); i++){
        month = month+ request[i];
      }
      for(int i = (request.indexOf("&")+1); i < request.indexOf("*"); i++){
        year = year + request[i];
      }
      Serial.print("h");
      delay(100);
      Serial.println(day);
      delay(100);
      Serial.println(month);
      delay(100);
      Serial.println(year);
    }
  else if  ( request.indexOf("s") > 0 ) {
      for(int i = (request.indexOf("s")+1); i < request.indexOf("o"); i++){
        hour = hour + request[i];
      }
      for(int i = (request.indexOf("o")+1); i < request.indexOf("&"); i++){
        minute = minute+ request[i];
      }
      Serial.print("s");
      delay(100);
      Serial.println(hour);
      delay(100);
      Serial.println(minute);
      delay(100);
      Serial.println("0");
    }

    // the LED is on so the button needs to say turn it off
    html_2 = "<form id='F1' action='u'><input class='button' type='submit' value='Big Clock' ></form><br>";
    // the LED is off so the button needs to say turn it on
    html_3 = "<form id='F1' action='t'><input class='button' type='submit' value='Celsius' ></form><br>";

    html_4 = "<form id='F1' action='d'><input class='button' type='submit' value='Date' ></form><br>";

    html_5 = "<form id='F1' action='w'><input class='button' type='submit' value='Creditos' ></form><br>";

    html_6 = "<form id='F1' action='b'><input class='button' type='submit' value='Brigtness' ></form><br>";

    html_7 = "<form id='F1' action='p'><input class='button' type='submit' value='Plasma' ></form><br>";
    
    html_8 = "<form id='F1' action='r'><input class='button' type='submit' value='Small Clock' ></form><br>";

    html_9 = "<form id='F1' action='f'><input class='button' type='submit' value='Fahrenheit' ></form><br>";
 
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );    
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4 );
    client.print( html_5 );
    client.print( html_6 );
    client.print( html_7 );
    client.print( html_8 );
    client.print( html_9 );
    client.print( end );
 
    delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} // void loop()