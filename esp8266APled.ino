/*
 * 2022 - 04 -03
 * Andrea --> https://github.com/andrebranz/esp8266APled
 */
/**
   1 - create an Access Point whit ESP8266 module
   2 - create and begin the server
   3 - configure the HTTP page to control the led
*/

// Read the readMe to find all Libraries you need
#include <ESP8266WiFi.h>


const char* ssid = "ESP8266";          //SSID (name) of the access Point
const char* password = "ESP8266Test";  //PASSWORD to connect to the access point
WiFiServer server(80);                 //create the istance of the server (port 80)

String request = "";                   // this String will memorize the page that, from HHTP page, we send the reques
int state;                             // this istance will memorize the state of the BuiltIn led

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);        // this is the default led, integredet on our ESP8266 module
  digitalWrite(LED_BUILTIN, HIGH);      // set default status
  delay(1000);
  Serial.begin(115200);                 // serial port of ESP8266 module comunicate on 115200 baud
  Serial.println();
  Serial.println();
  Serial.print("Crating the access point . . .");

  /*
     The next line is propbably the most important of our code.
     Whit this Function of WiFi libraries, we are creating our AP
     .softAP() retunr a boolean value, true if the access point is been created correctly else return false

     !! if we want a open AP, we cannot pass the password:
        example -->   boolean valueAP = WiFi.softAP(ssid);
  */
  boolean valueAP = WiFi.softAP(ssid, password);

  if (valueAP == true) { // if the Access Point is been created successfully

    IPAddress apIP = WiFi.softAPIP(); // get our IP
    Serial.println("Success!");
    Serial.println("");
    Serial.print("WiFi network name: ");
    Serial.println(ssid);
    Serial.print("WiFi network password: ");
    Serial.println(password);
    Serial.print("Host IP Address: ");
    Serial.println(apIP);
    Serial.println("");
    /*
       The next line begin the server (at the port 80), now we are using WiFiServer libraries
    */
    server.begin();
    Serial.println("server inizialized");
  }

  else {
    Serial.println("error! try to reload the program...");
  }

}

void loop() {
  WiFiClient client = server.available(); // set avaiable our server, whit begin  function we are only creating a server, but we are not leaving it available

  Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum()); // optional thing, print the number of devices connected to Acess Point
  delay(3000);
  
  if (!client) { // client memorize the WiFiClint object, if there are not a client
    return; //restart the loop
  }
  /*
     The first line of the request is the on that contain the command that we want to execute
  */
  request = client.readStringUntil('\r'); // continue to read the WiFiClient request until find "/r! subString


  if (request.indexOf("/LED=ON") != -1)  { // if the subString "/LED=ON" are not at the position -1 (error of the request)
    digitalWrite(LED_BUILTIN, LOW); // set LOW the led 
    state = LOW; // memorize the value of the led
  }
  if (request.indexOf("/LED=OFF") != -1)  { // if the subString "/LED=OFF" are not at the position -1 (error of the request)
    digitalWrite(LED_BUILTIN, HIGH); // set HIGH the led
    state = HIGH; //memorize the value of the led
  }
  // Reply to the request arrived at the server
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  !! this blank line is very important, after that we can write the HTML code 

  /*
   * The following code is written in HTML language 
   * To learn the basics of html you can use: https://www.w3schools.com/html/default.asp
   */
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=2\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");

  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: green; border-radius: 20px; color: white; padding: 32px 16px;");
  client.println("text-decoration: none; font-size: 40px; margin: 20px; cursor: pointer;}</style></head>");


  client.println("<body><h1>ESP8266 Access Point Andreabranz</h1>");
  client.print("<h2>STATE OF THE LED: </h2>");
  /*
   * This isn't a mistake, the builtIn led works differently 
   * When we say "stay high" it will be turned off
   * When we say "stay low" it will be turned on
   */
  if (state == HIGH) { // if the value (the request) is HIGH 
    client.print("<h3>OFF</h3>"); // print OFF
  } else {
    client.print("<h3>ON</h3>"); // print ON
  }
  client.println("<br><br>"); 
  client.println("<a href=\"/LED=ON\"\"><button class=\"button\">TURN ON </button></a>"); // this is a button ("TURN ON")
  client.println("<a href=\"/LED=OFF\"\"><button class=\"button\">TUNR OFF </button></a><br />"); // this is the second button ("TURN OFF")
  client.println("</html>"); // close HTML file

  delay(5); // wait 5ms, necessary to avoid possible loading errors
  
  // her the client will be disconnected, so the client variable has no value here
  
} // end of loop
