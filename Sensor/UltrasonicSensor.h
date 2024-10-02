#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor
{
private:
  int trigPin;
  int echoPin;

public:
  UltrasonicSensor(int trigPin, int echoPin)
  {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  float getDistance()
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration = pulseIn(echoPin, HIGH);

    Serial.print("Pulse duration: ");
    Serial.println(duration);

    if (duration == 0)
    {
      Serial.println("No pulse detected from the sensor.");
      return -1; 
    }

    float distance = duration * 0.034 / 2;

    Serial.print("Calculated distance: ");
    Serial.println(distance);

    return distance;
  }
};

#endif
