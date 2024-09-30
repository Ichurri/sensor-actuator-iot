#include <WiFi.h>

class WiFiManager
{
private:
  const char *ssid;
  const char *password;

public:
  WiFiManager(const char *ssid, const char *password)
  {
    this->ssid = ssid;
    this->password = password;
  }

  void connect()
  {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }
};