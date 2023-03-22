#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "Lights";
const char* password = "khaher4444";

const char* host = "www.googleapis.com";
const int httpsPort = 443;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;

    if (!client.connect(host, httpsPort)) {
      Serial.println("Connection failed");
      return;
    }

    String url = "/geolocation/v1/geolocate?key=your_API_key";
    String payload = "{\"considerIp\": \"true\"}";

    client.println(String("POST ") + url + " HTTP/1.1");
    client.println(String("Host: ") + host);
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(payload.length());
    client.println();
    client.println(payload);

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');

        if (line.startsWith("{\"location\"")) {
          DynamicJsonDocument doc(1024);
           deserializeJson(doc, line);
          float lat = doc["location"]["lat"];
          float lng = doc["location"]["lng"];
          Serial.print("Latitude: ");
          Serial.println(lat);
          Serial.print("Longitude: ");
          Serial.println(lng);
        }
      }
    }

    client.stop();
  }
  else {
    Serial.println("WiFi not connected");
  }

  delay(5000);
}