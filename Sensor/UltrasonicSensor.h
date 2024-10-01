#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

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
    return duration *0.034/2;
  }

};

#endif
