#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <WiFi.h>

class TcpClient
{
private:
  const char *serverIP;
  int serverPort;
  WiFiClient client;

public:
  TcpClient(const char *serverIP, int serverPort)
  {
    this->serverIP = serverIP;
    this->serverPort = serverPort;
  }

  bool connect()
  {
    if (client.connect(serverIP, serverPort))
    {
      Serial.println("Successfully connected to server.");
      return true;
    }
    else
    {
      Serial.println("Error connecting to server.");
      return false;
    }
  }

  void sendData(String data)
  {
    if (client.connected())
      client.println(data);
  }

  String receiveData()
  {
    String received = "";
    if (client.connected() && client.available())
    {
      received = client.readStringUntil('\n');
      received.trim();
    }
    return received;
  }

  bool isConnected()
  {
    return client.connected(); 
  }
};

#endif
