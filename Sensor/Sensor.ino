#include <WiFi.h>
#include "UltrasonicSensor.h"
#include "WiFiManager.h"
#include "TCPClient.h"

// Configuración de la red Wi-Fi y del servidor
const char *SSID = "Tu_SSID";
const char *PASSWORD = "Tu_PASSWORD";
const char *SERVER_IP = "192.168.1.100"; // IP del servidor Java
const int SERVER_PORT = 12345;           // Puerto del servidor

// Instanciación de las clases
WiFiManager wifiManager(SSID, PASSWORD);
TCPClient tcpClient(SERVER_IP, SERVER_PORT);
UltrasonicSensor sensor(5, 18); // Pines para el sensor ultrasónico (Trig: 5, Echo: 18)

void setup()
{
  Serial.begin(115200);

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
  // Leer la distancia del sensor ultrasónico
  float distance = sensor.getDistance();
  Serial.println("Distance: " + String(distance) + " cm");

  // Enviar la distancia al servidor Java
  tcpClient.sendData(String(distance));

  // Verificar si hay comandos del servidor (en este caso, no se espera ninguno)
  // Puedes implementar lógica adicional si es necesario

  delay(1000); // Espera de 1 segundo antes de la siguiente lectura
}
