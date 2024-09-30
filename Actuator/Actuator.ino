#include <WiFi.h>
#include "Led.h"
#include "LedManager.h"
#include "WiFiManager.h"
#include "TCPClient.h"

// Configuración de la red Wi-Fi y del servidor
const char *SSID = "Tu_SSID";
const char *PASSWORD = "Tu_Password";
const char *SERVER_IP = "192.168.1.100"; // IP del servidor Java
const int SERVER_PORT = 12345;           // Puerto del servidor

// Instanciación de las clases
WiFiManager wifiManager(SSID, PASSWORD);
TCPClient tcpClient(SERVER_IP, SERVER_PORT);

// Configuración de los LEDs
Led led1(4, 500);  // LED 1 en el pin 4
Led led2(5, 500);  // LED 2 en el pin 5
Led led3(18, 500); // LED 3 en el pin 18
LedManager ledManager(&led1, &led2, &led3);
Led manualLed(19, 1000); // LED manual en el pin 19

void setup()
{
  Serial.begin(115200);

  // Inicialización de LEDs
  led1.turnOff();
  led2.turnOff();
  led3.turnOff();
  manualLed.turnOff();

  // Conexión a WiFi
  wifiManager.connect();

  // Conexión al servidor TCP
  if (!tcpClient.connect())
  {
    Serial.println("Could not connect to the server. Rebooting...");
    ESP.restart();
  }
}

void loop()
{
  // Verificar si hay datos recibidos del servidor
  String command = tcpClient.receiveData();
  if (command.length() > 0)
  {
    Serial.println("Command received: " + command);

    // Decisiones automáticas basadas en la distancia
    float distance = command.toFloat();
    if (distance > 0)
    { // Asegurarse de que el comando sea una distancia válida
      if (distance < 20)
        ledManager.blinkLED(0); // LED 1
      else if (distance < 50)
        ledManager.blinkLED(1); // LED 2
      else
        ledManager.blinkLED(2); // LED 3
    }

    // Comandos manuales
    if (command == "ON")
      manualLed.update(); // Enciende el LED manual
    else if (command == "OFF")
      manualLed.turnOff(); // Apaga el LED manual
  }

  // Opcional: Implementar entrada manual desde el usuario (Serial)
  if (Serial.available())
  {
    String manualCommand = Serial.readStringUntil('\n');
    manualCommand.trim(); // Eliminar espacios en blanco
    if (manualCommand == "ON" || manualCommand == "OFF")
      tcpClient.sendData(manualCommand); // Enviar comando al servidor
  }

  delay(100); // Pequeña espera para evitar sobrecarga
}
