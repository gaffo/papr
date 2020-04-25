#include <TimerOne.h>

int fanPin = 9;
String inString = "";

void setup() {
  // Setup pins and zero them out
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  // setup PWM Module
  Timer1.initialize(40);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

const int d = 100;
int cur = 0;

void loop() {
  float val = float(cur / 100.0) * 1023;
  Serial.println(val);
  Timer1.pwm(fanPin, val);
  
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      cur = inString.toInt();
      inString = "";
      break;
    }
  }
  
  Serial.println(cur);
  delay(d);
}
