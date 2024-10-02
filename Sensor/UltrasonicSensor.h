#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor {
  private:
    int trigPin;
    int echoPin;

  public:
    UltrasonicSensor(int trigPin, int echoPin) {
      this->trigPin = trigPin;
      this->echoPin = echoPin;
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }

    float getDistance() {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      float duration = pulseIn(echoPin, HIGH);

      // Depuración: Imprimir la duración del pulso
      Serial.print("Duración del pulso: ");
      Serial.println(duration);

      if (duration == 0) {
        Serial.println("No se detectó ningún pulso del sensor.");
        return -1;  // Devuelve -1 si no se detecta una distancia válida
      }

      // Calcular la distancia en centímetros
      float distance = duration * 0.034 / 2;

      // Depuración: Imprimir la distancia calculada
      Serial.print("Distancia calculada: ");
      Serial.println(distance);

      return distance;
    }
};

#endif
