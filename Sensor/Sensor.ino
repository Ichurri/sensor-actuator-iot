#include "WiFiConnection.h"  // Incluir la clase WiFiConnection
#include "TCPClient.h"        // Incluir la clase TCPClient
#include "UltrasonicSensor.h" // Incluir la clase del sensor ultrasónico

WiFiConnection wifi("TECHLAB", "catolica11");  // Configura tu SSID y contraseña
TCPClient tcpClient("192.168.79.82", 1234);    // IP del servidor y puerto
UltrasonicSensor sensor(17, 16);                // Pines del sensor ultrasónico (TRIG, ECHO)

String currentState = "";  // Estado actual

void setup() {
  Serial.begin(115200);

  // Espera de 5 segundos antes de intentar conectarse
  Serial.println("Esperando antes de intentar conectar...");
  delay(5000);  // Espera 5 segundos

  // Conectar al WiFi
  wifi.connect();

  // Conectar al servidor TCP
  if (tcpClient.connect()) {
    Serial.println("Conectado al servidor TCP");
  } else {
    Serial.println("Error al conectar al servidor TCP");
  }

  // Pedir los estados al servidor
  tcpClient.sendData("GET_STATES");
  String states = tcpClient.receiveData();
  Serial.println("Estados recibidos: " + states);
}

void loop() {
  float distance = sensor.getDistance();  // Medir la distancia usando el sensor ultrasónico

  if (distance != -1) {  // Si la distancia es válida
    Serial.print("Distancia detectada: ");
    Serial.print(distance);
    Serial.println(" cm");

    String newState = "";

    // Determinar el estado basado en la distancia
    if (distance < 15) {
      newState = "STATE_RED";
    } else if (distance >= 15 && distance < 25) {
      newState = "STATE_YELLOW";
    } else if (distance >= 25 && distance < 40) {
      newState = "STATE_GREEN";
    } else {
      newState = "STATE_BLUE";
    }

    // Solo enviar el estado si ha cambiado
    if (newState != currentState) {
      Serial.println("Nuevo estado: " + newState);
      tcpClient.sendData(newState);  // Enviar el nuevo estado al servidor
      currentState = newState;  // Actualizar el estado actual
    }
  }

  delay(1000);  // Espera antes de la siguiente medición
}
