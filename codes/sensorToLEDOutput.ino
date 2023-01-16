int redLED = D4;
int blueLED = D7;
int sensor = A0;
#define MAX 65
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  int adcVal = analogRead(sensor);
  int dutyCycle1 = map(adcVal, 0, 1024, 0, 255);
  int dutyCycle2 = 255 - dutyCycle1;

  analogWrite(redLED, dutyCycle1);
  analogWrite(blueLED, dutyCycle2);
}
