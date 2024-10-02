#include "WiFiConnection.h"  // Incluir la clase WiFiConnection
#include "TCPClient.h"        // Incluir la clase TCPClient
#include "Led.h"              // Incluir la clase Led

// Configuración de WiFi y TCP
WiFiConnection wifi("TECHLAB", "catolica11");  // Ajusta tu SSID y contraseña WiFi
TCPClient tcpClient("192.168.79.82", 1234);      // Ajusta la IP del servidor y puerto

// Pines del LED
Led redLed(16);      // LED rojo en el pin 2
Led yellowLed(17);   // LED amarillo en el pin 3
Led greenLed(5);    // LED verde en el pin 4
Led blueLed(18);     // LED azul en el pin 5

void setup() {
  Serial.begin(115200);

  // Conectar al WiFi
  wifi.connect();

  // Conectar al servidor TCP
  if (tcpClient.connect()) {
    Serial.println("Conectado al servidor TCP.");
  } else {
    Serial.println("Error al conectar al servidor TCP.");
  }
}

void loop() {
  // Recibir datos del servidor
  String receivedState = tcpClient.receiveData();

  if (receivedState.length() > 0) {
    Serial.println("Estado recibido: " + receivedState);

    // Encender/apagar LEDs según el estado recibido
    if (receivedState == "STATE_RED") {
      redLed.turnOn();
      yellowLed.turnOff();
      greenLed.turnOff();
      blueLed.turnOff();
    } else if (receivedState == "STATE_YELLOW") {
      redLed.turnOff();
      yellowLed.turnOn();
      greenLed.turnOff();
      blueLed.turnOff();
    } else if (receivedState == "STATE_GREEN") {
      redLed.turnOff();
      yellowLed.turnOff();
      greenLed.turnOn();
      blueLed.turnOff();
    } else if (receivedState == "STATE_BLUE") {
      redLed.turnOff();
      yellowLed.turnOff();
      greenLed.turnOff();
      blueLed.turnOn();
    } else {
      // Si se recibe un estado desconocido, apagar todos los LEDs
      redLed.turnOff();
      yellowLed.turnOff();
      greenLed.turnOff();
      blueLed.turnOff();
    }
  }

  delay(1000);  // Espera antes de revisar el siguiente estado
}
