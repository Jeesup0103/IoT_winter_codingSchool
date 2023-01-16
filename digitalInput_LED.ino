int swL = D5;
int swR = D6;
int redLED = D4;
int blueLED = D7;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(swL, INPUT);
  pinMode(swR, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int swLVal = digitalRead(swL);
  int swRVal = digitalRead(swR);

  if(swLVal == 0){
    digitalWrite(redLED, HIGH);
  }
  else{
    digitalWrite(redLED, LOW);
  }
  if(swRVal == 0){
    digitalWrite(blueLED, HIGH);
  }
  else{
    digitalWrite(blueLED, LOW);
  }

  Serial.print(swLVal);
  Serial.println(swRVal);
  

}
