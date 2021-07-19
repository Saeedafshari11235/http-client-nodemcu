//it's a program that connect to a server and share information using http
//add libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
//set the connection information
const char* ssid = "Afshari-tcz";
const char* password = "Saeed@#Hesam";
//set a pin to get the value of pot
const int analogInPin = A0;
//value of pot
int sensorValue = 0;
//name of server and the port
String serverName = "http://arha83.pythonanywhere.com/:443";
//i don't why it is here but code works
unsigned long lastTime = 0;
//delay of sending info
unsigned long timerDelay = 3000;

void setup() {
  //set the speed
  Serial.begin(115200);
  //connecting to the wifi
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  //while the device is not connected...
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  //print the wifi ip
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
}


void loop() {
  //get the value of sensor from pin
  sensorValue = analogRead(analogInPin);

  if ((millis() - lastTime) > timerDelay) {
    //if the wifi is still connected
    if (WiFi.status() == WL_CONNECTED) {
      //Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().--->Arduino.cc
      WiFiClient client;
      //make a var as httpclient 
      HTTPClient http;
      //make a web address using GET method and put it in a string var
      //for GET method use "/?" at first and use "&" to separate information
      String serverPath = serverName + "/?username=nodemcu" + "&" + "pot=" + String(sensorValue);
      Serial.print("\npotValue : ");
      Serial.println(sensorValue);
      delay(500);
      //begins connecting to server
      //i don't know what c_str()is
      http.begin(client, serverPath.c_str());
      //get the response code using GET
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
