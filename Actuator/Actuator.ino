#include <WiFi.h>
#include "Led.h"
#include "WiFiConnection.h"
#include "TcpClient.h"

// Configuración de la red Wi-Fi y del servidor
const char *SSID = "Tu_SSID";
const char *PASSWORD = "Tu_Password";
const char *SERVER_IP = "192.168.1.100"; // IP del servidor Java
const int SERVER_PORT = 12345;           // Puerto del servidor

// Instanciación de las clases
WiFiConnection wifiConnection(SSID, PASSWORD);
TcpClient tcpClient(SERVER_IP, SERVER_PORT);

// Configuración de los LEDs
Led ledRed(4, 500);    // LED rojo en el pin 4
Led ledYellow(5, 500); // LED amarillo en el pin 5
Led ledGreen(18, 500); // LED verde en el pin 18
Led ledBlue(19, 1000); // LED azul (manual) en el pin 19

void setup()
{
  Serial.begin(115200);

  // Inicialización de LEDs
  ledRed.turnOff();
  ledYellow.turnOff();
  ledGreen.turnOff();
  ledBlue.turnOff();

  // Conexión a WiFi
  wifiConnection.connect();

  // Conexión al servidor TCP
  if (!tcpClient.connect())
  {
    Serial.println("No se pudo conectar al servidor. Reiniciando...");
    ESP.restart();
  }
}

void loop()
{
  // Verificar si hay datos recibidos del servidor
  String command = tcpClient.receiveData();
  if (command.length() > 0)
  {
    Serial.println("Comando recibido: " + command);

    // Decisiones automáticas basadas en la distancia
    float distance = command.toFloat();
    if (distance > 0)
    { // Asegurarse de que el comando sea una distancia válida
      if (distance < 15)
      {
        ledRed.update(); // Encender LED rojo
        ledYellow.turnOff();
        ledGreen.turnOff();
      }
      else if (distance < 35)
      {
        ledYellow.update(); // Encender LED amarillo
        ledRed.turnOff();
        ledGreen.turnOff();
      }
      else if (distance < 60)
      {
        ledGreen.update(); // Encender LED verde
        ledRed.turnOff();
        ledYellow.turnOff();
      }
      else
      {
        ledRed.turnOff();
        ledYellow.turnOff();
        ledGreen.turnOff();
      }
    }

    // Comandos manuales para el LED azul
    if (command == "ON")
      ledBlue.update(); // Enciende el LED azul
    else if (command == "OFF")
      ledBlue.turnOff(); // Apaga el LED azul
  }

  delay(100); // Pequeña espera para evitar sobrecarga
}
