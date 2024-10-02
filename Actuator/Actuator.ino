#include "WiFiConnection.h" 
#include "TcpClient.h"      
#include "Led.h"            

WiFiConnection wifi("iPhone de Santiago", "21Santi03Saa04$$"); 
TcpClient tcpClient("172.20.10.9", 1234);            

Led redLed(16, 1000);    
Led yellowLed(17, 1000); 
Led greenLed(5, 1000);   
Led blueLed(18, 1000);   

void setup()
{
    Serial.begin(115200);

    wifi.connect();

    if (tcpClient.connect())
        Serial.println("Connected to TCP server.");
    else
        Serial.println("Error connecting to TCP server.");
}

void loop()
{
    String receivedState = tcpClient.receiveData();

    if (receivedState.length() > 0)
    {
        Serial.println("State received: " + receivedState);

        if (receivedState == "STATE_RED")
        {
            redLed.update();
            yellowLed.turnOff();
            greenLed.turnOff();
            blueLed.turnOff();
        }
        else if (receivedState == "STATE_YELLOW")
        {
            redLed.turnOff();
            yellowLed.update();
            greenLed.turnOff();
            blueLed.turnOff();
        }
        else if (receivedState == "STATE_GREEN")
        {
            redLed.turnOff();
            yellowLed.turnOff();
            greenLed.update();
            blueLed.turnOff();
        }
        else if (receivedState == "STATE_BLUE")
        {
            redLed.turnOff();
            yellowLed.turnOff();
            greenLed.turnOff();
            blueLed.update();
        }
        else
        {
            redLed.turnOff();
            yellowLed.turnOff();
            greenLed.turnOff();
            blueLed.turnOff();
        }
    }

    delay(100); 
}
