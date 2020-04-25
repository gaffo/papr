#include <TimerOne.h>
#include <AutoPID.h>
//#include <Arduino_DebugUtils.h>

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
  attachInterrupt(digitalPinToInterrupt(rpmFan), rpmPulse, RISING);
  
  // setup PWM Module
  Timer1.initialize(40);
  Serial.begin(9600);
//  Debug.timestampOn();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  delay(100);
  Serial.println(rpmPulses);
  long delta = long(millis() - lastSample);

  double rpMs = (rpmPulses / double(delta)); // to minutes
  rpmPulses = 0;
  lastSample = millis();
  
  float val = float(10.0 / 100.0) * 1023;
  Timer1.pwm(fanPin, val);
}
