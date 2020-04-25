#include <TimerOne.h>
#include <AutoPID.h>

int fanPin = 9;
int rpmFan = 2;

long lastSample = 0;
long rpmPulses = 0;

void rpmPulse() {
  rpmPulses++;
}

void setup() {
  // Setup pins and zero them out
  pinMode(fanPin, OUTPUT);
  pinMode(rpmFan, INPUT_PULLUP);
  lastSample = millis();
  attachInterrupt(digitalPinToInterrupt(rpmFan), rpmPulse, HIGH);
  
  // setup PWM Module
  Timer1.initialize(40);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  delay(100);
  Serial.println(rpmPulses);
//  float delta = float(millis() - lastSample);
//  Serial.println(delta);
//  double rpm = (rpmPulses / delta) / 1000.0 / 60.0;
//  Serial.println(rpm);
  rpmPulses = 0;
  lastSample = millis();
  
  float val = float(10.0 / 100.0) * 1023;
  Timer1.pwm(fanPin, val);
}
