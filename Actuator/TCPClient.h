#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <WiFi.h>

class TCPClient {
  private:
    const char* serverIP;
    int serverPort;
    WiFiClient client;

  public:
    TCPClient(const char* serverIP, int serverPort) {
      this->serverIP = serverIP;
      this->serverPort = serverPort;
    }

    bool connect() {
      // Cerrar cualquier conexión existente antes de reconectar
      if (client.connected()) {
        client.stop();  // Detener la conexión anterior
        Serial.println("Conexión anterior cerrada.");
      }

      // Intentar conectar de nuevo
      if (client.connect(serverIP, serverPort)) {
        Serial.println("Conexión al servidor exitosa.");
        return true;
      } else {
        Serial.println("Error al conectar al servidor.");
        return false;
      }
    }

    void sendData(String data) {
      if (client.connected()) {
        Serial.println("Enviando datos al servidor: " + data);  // Depuración adicional
        client.println(data);
      } else {
        Serial.println("No hay conexión al servidor. Reconectando...");
        if (connect()) {  // Intentar reconectar
          Serial.println("Reconectado. Enviando datos.");
          client.println(data);  // Enviar datos después de reconectar
        } else {
          Serial.println("No se pudo reconectar.");
        }
      }
    }

    String receiveData() {
      String received = "";
      if (client.connected() && client.available()) {
        received = client.readStringUntil('\n');
        received.trim();
      } else {
        Serial.println("No se recibieron datos del servidor.");
      }
      return received;
    }
};

#endif
