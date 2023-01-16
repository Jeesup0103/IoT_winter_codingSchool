int buzzer = D4;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  tone(buzzer, 261);
  delay(1000);
  tone(buzzer, 329);
  delay(1000);
  tone(buzzer, 392);
  delay(1000);
}
