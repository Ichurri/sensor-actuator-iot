#include <WiFi.h>
#include "UltrasonicSensor.h"

// Definir las credenciales de la red WiFi
const char* ssid = "tuSSID";
const char* password = "tuPassword";

// Dirección IP y puerto del servidor Java
const char* serverIP = "192.168.1.100"; // Dirección IP del servidor
const int serverPort = 12345;

// Crear una instancia del sensor ultrasónico
UltrasonicSensor sensor(5, 18); // Ajustar pines del sensor (trigPin, echoPin)

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Conectar a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a WiFi");
  
  // Intentar conectarse al servidor
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Conectado al servidor TCP");
  } else {
    Serial.println("Error al conectar al servidor");
  }
}

void loop() {
  // Obtener la distancia medida por el sensor ultrasónico
  float distance = sensor.getDistance();
  Serial.println("Distancia: " + String(distance) + " cm");
  
  // Enviar la distancia al servidor
  if (client.connected()) {
    client.print(String(distance));
    client.print("\n"); // Enviar nueva línea para finalizar el mensaje
  } else {
    Serial.println("Desconectado del servidor");
  }
  
  delay(2000); // Esperar 2 segundos antes de la siguiente medición
}
