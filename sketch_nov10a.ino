#include <ESP8266WiFi.h>
#include <DHT.h>
#include "ThingSpeak.h"

DHT dht11(D4, DHT11);


unsigned long channelID = 2340720;
const char* writeKey = "JLSZABAB2Z0UOT2X";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  init_wifi("Chatree01", "0620565502");
  ThingSpeak.begin(client);
}

void init_wifi(String ssid, String password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  float humid = dht11.readHumidity();
  float temp = dht11.readTemperature();
  ThingSpeak.setField(1, humid);
  ThingSpeak.setField(2, temp);
  int x = ThingSpeak.writeFields(channelID, writeKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(16000);
}
