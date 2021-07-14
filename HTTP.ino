#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Afshari-tcz";
const char* password = "Saeed@#Hesam";
const int analogInPin = A0;

int sensorValue = 0;
String serverName = "http://192.168.1.50:8000";
unsigned long lastTime = 0;
unsigned long timerDelay = 200;
int pot;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}


void loop() {
  sensorValue = analogRead(analogInPin);

  if ((millis() - lastTime) > timerDelay) {

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      String serverPath = serverName + "/?username=nodemcu" + "&" + "pot=" + String(sensorValue);
      Serial.print("\npotValue : ");
      Serial.println(sensorValue);
      delay(500);
      http.begin(client, serverPath.c_str());
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
