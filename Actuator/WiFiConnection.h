#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <WiFi.h>

class WiFiConnection {
  private:
    const char* ssid;
    const char* password;

  public:
    WiFiConnection(const char* ssid, const char* password) {
      this->ssid = ssid;
      this->password = password;
    }

    void connect() {
      WiFi.begin(ssid, password);
      Serial.println("Connecting to WiFi...");
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
      }
      Serial.println("\nConnected to WiFi");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    }
};

#endif
