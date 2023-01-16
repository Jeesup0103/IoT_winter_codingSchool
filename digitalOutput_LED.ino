int redLED = D4;
int blueLED = D7;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(redLED, HIGH);
  delay(100);
  digitalWrite(redLED, LOW);
  
  digitalWrite(blueLED, HIGH);
  delay(100);
  digitalWrite(blueLED, LOW);
}
