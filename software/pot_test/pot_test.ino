#define SPEED_IN A1
#define SPEED_IN_OFF 200
#define SPEED_IN_MAX 870


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

int readings[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int lenReadings = sizeof(readings)/sizeof(int);
int count = 0;

void loop() {
  delay(10);
  count++;
  int reading = analogRead(SPEED_IN);
  for (int i = 0; i < (lenReadings - 1); i++) {
    readings[i] = readings[i+1]; // shufle down
  }
  readings[lenReadings - 1] = reading;

  if (count % lenReadings != 0) {
    return;
  }
  
  count = 0;
  int sum = 0;
  for (int i = 0; i < lenReadings; i++) {
    sum += readings[i];
//    Serial.println(readings[i]);
  }
  reading = sum / lenReadings;
//  Serial.println("-----");
  if (reading > SPEED_IN_MAX) {
    Serial.println("MAX");
  }
  else if (reading < SPEED_IN_OFF) {
    Serial.println("OFF");
  } else {
    float pct = (reading - SPEED_IN_OFF) / float((SPEED_IN_MAX - SPEED_IN_OFF));
    pct = pct * 100.0;
    Serial.println(pct);
  }
  
}
