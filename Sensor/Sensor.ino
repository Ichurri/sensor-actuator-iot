#include <WiFi.h>
#include "UltrasonicSensor.h"

// Definir las credenciales de la red WiFi
const char* SSID = "tuSSID";
const char* PASSWORD = "tuPassword";

// Dirección IP y puerto del servidor Ja  va
const char* SERVER_IP = "192.168.56.1"; // Dirección IP del servidor
const int SERVER_PORT = 12345;

UltrasonicSensor sensor(5, 18); // Ajustar pines del sensor (trigPin, echoPin)

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Conectar a la red WiFi
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  
  // Intentar conectarse al servidor
  if (client.connect(SERVER_IP, SERVER_PORT))
    Serial.println("Connected to TCP Server");
  else
    Serial.println("Error connecting to server");
}

void loop() {
  // Obtener la distancia medida por el sensor ultrasónico
  float distance = sensor.getDistance();
  Serial.println("Distance: " + String(distance) + " cm");
  
  // Enviar la distancia al servidor
  if (client.connected()) {
    client.print(String(distance));
    client.print("\n"); // Enviar nueva línea para finalizar el mensaje
  } else 
  
  delay(2000); // Esperar 2 segundos antes de la siguiente medición
}
