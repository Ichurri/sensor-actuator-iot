#include "Led.h"

class LedManager {
  private:
    Led* leds[3];

  public:
    LedManager(Led* led1, Led* led2, Led* led3) {
      leds[0] = led1;
      leds[1] = led2;
      leds[2] = led3;
    }

    void blinkLED(int indexToBlink) {
      for (int i = 0; i < 3; i++) {
        if (i == indexToBlink) 
          leds[i]->update();  // Blink the selected Led
        else
          leds[i]->turnOff();  // Ensure others are off
      }
    }
};