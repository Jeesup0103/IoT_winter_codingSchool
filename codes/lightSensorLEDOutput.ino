int sensor = A0;
int redLED = D4;
int blueLED = D7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adcVal = analogRead(sensor);
  if(0 <= adcVal && adcVal < 300){
     digitalWrite(redLED, HIGH);
     digitalWrite(blueLED, LOW);
  }
  else if(300 <= adcVal && adcVal <700){
     digitalWrite(redLED, LOW);
     digitalWrite(blueLED, HIGH);
  }
  else {
     digitalWrite(redLED, HIGH);
     digitalWrite(blueLED, HIGH);
  }
  Serial.println(adcVal);
  delay(100);
}
