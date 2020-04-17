/*

Class example for Intangible Interaction at ITP

This sketch gets the most recent weather and pollution data of a selected city 
from api.airvisual.com
and parse the response to get the aqius (air quality index US) 
to illuminated different colors of LED that indicate the air quality

Wiring (Arduino IoT33):
D5 - 220k - Green LED
D6 - 220k - Yellow LED
D7 - 220k - Red LED

*/

#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" // to keep sensitive information on a sepearate file 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

const char serverAddress[] = "api.airvisual.com";  // server address
int port = 443;
String API = "ba1ee32e-89c8-45ba-8ae3-1e389ff7de71";
String cityName = "Seoul";
String stateName = "Seoul";
String countryName = "South%20Korea";

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

int aqi_city;

void setup() {

  Serial.begin(9600);

  connectWifi();

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
   
}

void loop() {
  
  getData();
  
  Serial.print(aqi_city);

  // turn on different colors of LEDs depending on the US EPA Air Quality Index
  if (aqi_city < 50 && aqi_city >= 0) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  } else if (aqi_city >= 50 && aqi_city <100) {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  } else {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }

  delay(10000);
}

void getData() {

  // assemble the path for the GET message:
  String path = "/v2/city?city=" + cityName + "&state=" + stateName + "&country=" + countryName + "&key=" + API;
  String contentType = "application/json";
  
  // send the GET request
  Serial.println("making GET request");
  Serial.println(path);   
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  // parse the response to get the value of aqius 
  int labelStart = response.indexOf("aqius");
  int valueStart = response.indexOf(":", labelStart);
  int valueEnd = response.indexOf(",", labelStart);
  String valueS = response.substring(valueStart + 1, valueEnd);
  int valueN = valueS.toInt();
  Serial.println(valueN);

  // convert the string to int
  aqi_city = valueS.toInt();  
   
}


void connectWifi() {
  
  while (!Serial);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);     // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}
