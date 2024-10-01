#ifndef TCPCLIENT_H
#define TCPCLIENT_H

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
      Serial.print("Connecting to server at ");
      Serial.print(serverIP);
      Serial.print(":");
      Serial.println(serverPort);
      
      if (client.connect(serverIP, serverPort)) {
        Serial.println("Connected to the server");
        return true;
      } else {
        Serial.println("Failed to connect to the server");
        return false;
      }
    }

    void sendData(String data) {
      if (client.connected()) {
        client.print(data);  // Send data as a string to the server
        Serial.println("Data sent: " + data);
      } else {
        Serial.println("Client not connected. Reconnecting...");
        connect();  // Try to reconnect if connection is lost
      }
    }

    String receiveData() {
      String received = "";
      if (client.connected() && client.available()) {
        received = client.readStringUntil('\n');  // Read the incoming data
        received.trim();  // Remove any trailing whitespace/newlines
        Serial.println("Data received: " + received);
      }
      return received;
    }
};

#endif
