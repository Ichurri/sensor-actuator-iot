#ifndef LED_H
#define LED_H

class Led {
  private:
    int pin;
    bool state;

  public:
    Led(int pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
      state = LOW;
      digitalWrite(pin, state);
    }

    void turnOn() {
      state = HIGH;
      digitalWrite(pin, state);
    }

    void turnOff() {
      state = LOW;
      digitalWrite(pin, state);
    }

    void toggle() {
      state = !state;
      digitalWrite(pin, state);
    }
};

#endif
