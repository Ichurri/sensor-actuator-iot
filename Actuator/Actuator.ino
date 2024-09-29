#include <WiFi.h>
#include "Led.h"

// Definir las credenciales de la red WiFi
const char* ssid = "tuSSID";
const char* password = "tuPassword";

// Dirección IP y puerto del servidor Java
const char* serverIP = "192.168.1.100"; // Dirección IP del servidor
const int serverPort = 12345;

// Crear una instancia del actuador LED
Led led(13, 1000); // Pin 13 para el LED y un intervalo de 1 segundo

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
  // Revisar si hay datos disponibles desde el servidor
  if (client.available()) {
    String command = client.readStringUntil('\n');
    Serial.println("Comando recibido: " + command);
    
    // Controlar el LED según el comando recibido
    if (command == "ON") {
      led.update(); // Encender el LED
    } else if (command == "OFF") {
      led.turnOff(); // Apagar el LED
    }
  }

  delay(1000); // Evitar sobrecarga en la comunicación
}
