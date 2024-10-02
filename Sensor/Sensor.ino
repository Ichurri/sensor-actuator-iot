#include "WiFiConnection.h"   
#include "TcpClient.h"        
#include "UltrasonicSensor.h" 

WiFiConnection wifi("iPhone de Santiago", "21Santi03Saa04$$"); 
TcpClient tcpClient("172.20.10.9", 1234); 
UltrasonicSensor sensor(17, 16);               

String currentState = ""; 

void setup()
{
  Serial.begin(115200);

  wifi.connect();

  reconnectToServer();

  tcpClient.sendData("GET_STATES");
  String states = tcpClient.receiveData();
  Serial.println("States received: " + states);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi disconnected. Attempting to reconnect...");
    wifi.connect();
  }

  if (!tcpClient.isConnected())
    reconnectToServer();

  float distance = sensor.getDistance();

  if (distance != -1)
  { 
    Serial.print("Distance detected: ");
    Serial.print(distance);
    Serial.println(" cm");

    String newState = "";

    if (distance < 15)
      newState = "STATE_RED";
    else if (distance >= 15 && distance < 25)
      newState = "STATE_YELLOW";
    else if (distance >= 25 && distance < 40)
      newState = "STATE_GREEN";
    else
      newState = "STATE_BLUE";

    if (newState != currentState)
    {
      Serial.println("New state: " + newState);
      tcpClient.sendData(newState); 
      currentState = newState;      
    }
  }

  delay(1000); 
}

void reconnectToServer()
{
  Serial.println("Attempting to connect to TCP server...");
  if (tcpClient.connect())
    Serial.println("Connected to TCP server");
  else
  {
    Serial.println("Error connecting to TCP server. Retrying...");
    delay(5000); 
    reconnectToServer();
  }
}
