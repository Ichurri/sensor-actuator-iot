#include <WiFi.h>
#include "UltrasonicSensor.h"
#include "WiFiConnection.h"
#include "TcpClient.h"

// Configuración de la red Wi-Fi y del servidor
const char *SSID = "LABO17";
const char *PASSWORD = "catolica17";
const char *SERVER_IP = "192.168.79.82"; // IP del servidor Java
const int SERVER_PORT = 12345;           // Puerto del servidor

// Instanciación de las clases
WiFiConnection wifiConnection(SSID, PASSWORD);
TcpClient tcpClient(SERVER_IP, SERVER_PORT);
UltrasonicSensor sensor(17, 16); // Pines para el sensor ultrasónico (Trig: 5, Echo: 18)

void setup()
{
  Serial.begin(115200);

  // Conexión a WiFi
  wifiConnection.connect();

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
