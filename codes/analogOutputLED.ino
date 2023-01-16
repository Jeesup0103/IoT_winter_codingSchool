int redLED = D4;
int blueLED = D7;
#define MAX 65
void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:

  int i = 0;
  for(i=0; i <= MAX; i++){
    analogWrite(redLED, i);
    analogWrite(blueLED, i);
    delay(5);
  }
  for(i=MAX; i >= 0; i--){
    analogWrite(redLED, i);
    analogWrite(blueLED, i);
    delay(5);
  }

}
