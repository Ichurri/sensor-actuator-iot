#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
  int pin;
  bool state;
  unsigned long previousMillis;
  const long interval;

public:
  Led(int pin, long interval)
      : pin(pin), state(LOW), previousMillis(0), interval(interval)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state);
  }

  void update()
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      state = !state; 
      digitalWrite(pin, state);
    }
  }

  void turnOff()
  {
    state = LOW;
    digitalWrite(pin, state);
  }
};

#endif
