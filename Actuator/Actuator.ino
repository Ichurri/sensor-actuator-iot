#include <WiFi.h>
#include "Led.h"

// Definir las credenciales de la red WiFi
const char* SSID = "tuSSID";
const char* PASSWORD = "tuPassword";

// Dirección IP y puerto del servidor Java
const char* SERVER_IP = "192.168.56.1"; // Dirección IP del servidor
const int SERVER_PORT = 12345;

Led led(13, 1000); 

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
  if (client.connect(SERVER_IP, SERVER_PORT)) {
    Serial.println("Connected to TCP Server");
  } else {
    Serial.println("Error connecting to server");
  }
}

void loop() {
  // Revisar si hay datos disponibles desde el servidor
  if (client.available()) {
    String command = client.readStringUntil('\n');
    Serial.println("Command received: " + command);
    
    // Controlar el LED según el comando recibido
    if (command == "ON") {
      led.update(); // Encender el LED
    } else if (command == "OFF") {
      led.turnOff(); // Apagar el LED
    }
  }

  delay(1000); // Evitar sobrecarga en la comunicación
}
