#include "UltrasonicSensor.h"
#include "LedManager.h"

const int LEDPINS[] = {27, 26, 25};
float cm = 0;

UltrasonicSensor sensor(22, 23);
Led led1(27, 300);
Led led2(26, 300);
Led led3(25, 300);
LedManager ledManager(&led1, &led2, &led3);

void setup() {
  Serial.begin(9600); 
}

void loop() {
  float distance = sensor.getDistance();
  int ledIndexToBlink = -1;
  cm = distance;

  if (distance < 15)
    ledIndexToBlink = 2;
  else if (distance < 35)
    ledIndexToBlink = 1;
  else if (distance < 60)
    ledIndexToBlink = 0;

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  ledManager.blinkLED(ledIndexToBlink);
}