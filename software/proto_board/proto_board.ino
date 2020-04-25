#include <TimerOne.h>

int fanPin = 9;

void setup() {
  // Setup pins and zero them out
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  // setup PWM Module
  Timer1.initialize(40);
}

const int d = 500;

void loop() {
  // slowly increase the PWM fan speed
  for (float dutyCycle = 0.0; dutyCycle < 100.0; dutyCycle++) {
    Serial.print("PWM Fan, Duty Cycle = ");
    Serial.println(dutyCycle);
    Timer1.pwm(fanPin, (dutyCycle / 100) * 1023);
//    analogWrite(fanPin, (dutyCycle / 100) * 255);
    delay(d);
  }
  for (float dutyCycle = 100; dutyCycle > 0.0; dutyCycle--) {
    Serial.print("PWM Fan, Duty Cycle = ");
    Serial.println(dutyCycle);
    Timer1.pwm(fanPin, (dutyCycle / 100) * 1023);
//    analogWrite(fanPin, (dutyCycle / 100) * 255);
    delay(d);
  }
}
