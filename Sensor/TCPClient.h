#include <WiFi.h>

class TCPClient {
  private:
    const char* serverIP;
    int serverPort;
    WiFiClient client;

  public:
    TCPClient(const char* serverIP, int serverPort) {
      this->serverIP = serverIP;
      this->serverPort = serverPort;
    }

    bool connect() {
      Serial.print("Connecting to TCP server on ");
      Serial.print(serverIP);
      Serial.print(":");
      Serial.println(serverPort);
      if (client.connect(serverIP, serverPort)) {
        Serial.println("Connected to TCP server");
        return true;
      } else {
        Serial.println("Failure to connect to TCP server");
        return false;
      }
    }

    void sendData(String data) {
      if (client.connected()) {
        client.println(data);
        Serial.println("Data sent: " + data);
      } else {
        Serial.println("Not connected to the server. trying to reconnect...");
        connect();
      }
    }

    // En este nodo no esperamos recibir datos, pero se puede implementar si es necesario
    String receiveData() {
      String received = "";
      if (client.available()) {
        received = client.readStringUntil('\n');
        Serial.println("Datos recibidos: " + received);
      }
      return received;
    }
};

